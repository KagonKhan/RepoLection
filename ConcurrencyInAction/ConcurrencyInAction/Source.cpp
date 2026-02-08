#include <iostream>
#include <thread>
#include <syncstream>
#include "ThreadSafeContainers.h"
#include "ComplexSafeContainers.h"

#include "Auxiliary.h"
#include <mutex>


std::atomic<bool> done{false};
const int amount = 5'000;


void basic_queue() {
	SafeQueue<int> q;

	auto produce = [&](SafeQueue<int>& q) {
		for (int i = 0; i < amount; i++) {
			q.push(rand() % 50);
		}

		done.store(true, std::memory_order_release);
	};
	auto consume = [&](SafeQueue<int>& q) {
		std::shared_ptr<int> item;
		while (!done.load(std::memory_order_acquire) || !q.empty()) {
			if (!q.try_pop(item)) continue;
			std::osyncstream(std::cout) << *item << "\n";
		}
	};

	std::jthread producer{ produce, std::ref(q) };
	std::vector<std::jthread> consumers;

	for (int i = 0; i < 5; i++) {
		consumers.emplace_back(consume, std::ref(q));
	}

}

void basic_wait_queue() {
	WaitingSafeQueue<int> q;

	auto produce = [&](WaitingSafeQueue<int>& q) {
		for (int i = 0; i < amount; i++) {
			q.push(rand() % 50);
		}

		done.store(true, std::memory_order_release);
	};
	auto consume = [&](WaitingSafeQueue<int>& q) {
		while (!done.load(std::memory_order_acquire) || !q.empty()) {
			std::osyncstream(std::cout) << *q.wait_pop() << "\n";
		}
	};

	std::jthread producer{ produce, std::ref(q) };
	std::vector<std::jthread> consumers;

	for (int i = 0; i < 5; i++) {
		consumers.emplace_back(consume, std::ref(q));
	}

}

void basic_list() {
	SafeList<int> q;

	auto produce = [&](SafeList<int>& q) {
		for (int i = 0; i < amount; i++) {
			q.push(rand() % 50);
		}

		done.store(true, std::memory_order_release);
	};
	auto consume = [&](SafeList<int>& q) {
		while (!done.load(std::memory_order_acquire) || !q.empty()) {
			if(auto item = q.pop_front(); item) std::osyncstream(std::cout) << *item << "\n";
		}
	};

	std::jthread producer{ produce, std::ref(q) };
	std::vector<std::jthread> consumers;

	for (int i = 0; i < 5; i++) {
		consumers.emplace_back(consume, std::ref(q));
	}

}

void finesafeq() {
	FineSafeQueue<int> q;

	auto produce = [&](FineSafeQueue<int>& q) {
		for (int i = 0; i < amount; i++) {
			auto item = rand() % 50;
			std::osyncstream(std::cout) << "Storing " << item << "\n";
			q.push(item);
		}

		done.store(true, std::memory_order_release);
	};

	//auto consume = [&](FineSafeQueue<int>& q) {
	//	while (!done.load(std::memory_order_acquire) || !q.empty()) {
	//		if(auto item = q.tryPop(); item) std::osyncstream(std::cout) << "Popping: " << *item << "\n";
	//	}
	//};


	std::vector<std::jthread> producers, consumers;
	for (int i = 0; i < 1; i++) {
		producers.emplace_back(produce, std::ref(q));
	}

	//for (int i = 0; i < 5; i++) {
	//	consumers.emplace_back(consume, std::ref(q));
	//}

}








void OWN_join_thread() {
	std::thread t1{ [] {
		for (int i = 0; i < 10; i++) std::cout << "Thread 1\n";
	}};

	jthread t2{ std::move(t1) };
}

void OWN_data_race() {
	int integer{0};
	std::jthread t1{ [&] {for (int i = 0; i < 1'000'000; i++) ++integer;}};
	std::jthread t2{ [&] {for (int i = 0; i < 1'000'000; i++) ++integer;}};
	t1.join(); t2.join();

	std::cout << "[INTEGER]\tExpected {2'000'000}, received {" << integer << "}\n";



	std::atomic<int> atomic_integer{ 0 };
	std::jthread t3{ [&] {for (int i = 0; i < 1'000'000; i++) ++atomic_integer; } };
	std::jthread t4{ [&] {for (int i = 0; i < 1'000'000; i++) ++atomic_integer; } };
	t3.join(); t4.join();

	std::cout << "[ATOMIC]\tExpected {2'000'000}, received {" << atomic_integer << "}\n";
}

void OWN_deadlock(bool deadlock) {
	if (deadlock) {
		std::mutex m1, m2;
		int integer{ 0 };

		std::jthread t1{ [&] {for (int i = 0; i < 1'000'000; i++) {
				{
					std::cout << "Thread1 locking \n";
					std::lock_guard lock1(m1);
					std::lock_guard lock2(m2);
					integer++;
					std::cout << "[INTEGER]\t {" << integer << "}\n";
				}
		}} };

		std::jthread t2{ [&] {for (int i = 0; i < 1'000'000; i++) {
				{
					std::cout << "Thread2 locking \n";
					std::lock_guard lock2(m2);
					std::lock_guard lock1(m1);
					integer++;
					std::cout << "[INTEGER]\t {" << integer << "}\n";
				}
		}} };

		t1.join(); t2.join();
		std::cout << "[INTEGER]\tExpected {2'000'000}, received {" << integer << "}\n";
	}
	else {
		std::mutex m1, m2;
		int integer{ 0 };

		std::jthread t1{ [&] {for (int i = 0; i < 100'000; i++) {
				{
					std::cout << "Thread1 locking\t";
					std::scoped_lock s(m2, m1);
					//std::lock_guard lock1(m1);
					//std::lock_guard lock2(m2);
					integer++;
					std::cout << "[INTEGER]\t {" << integer << "}\n";
				}
		}} };

		std::jthread t2{ [&] {for (int i = 0; i < 100'000; i++) {
				{
					std::cout << "Thread2 locking\t";
					std::scoped_lock s(m1, m2);
					//std::lock_guard lock1(m1);
					//std::lock_guard lock2(m2);
					integer++;
					std::cout << "[INTEGER]\t {" << integer << "}\n";
				}
		}} };

		t1.join(); t2.join();
		std::cout << "[INTEGER]\tExpected {2'000'000}, received {" << integer << "}\n";
	}
}

void OWN_spinlock() {
	spinlock spin;
	int integer{ 0 };
	int length{ 10'000'000 };
	std::jthread t1{ [&] {for (int i = 0; i < length; i++) {
		spin.lock();
		integer++;
		spin.unlock();
	}} };

	std::jthread t2{ [&] {for (int i = 0; i < length; i++) {
		spin.lock();
		integer++;
		spin.unlock();
	}} };

	t1.join(); t2.join();
	std::cout << "[INTEGER]\tExpected {" << length*2 << "}, received {" << integer << "}\n";

}

void OWN_unique_lock() {
	std::mutex mutex;

	int integer{ 0 };
	int length{ 10'000'000 };

	std::jthread t1{ [&] {for (int i = 0; i < length; i++) {
		unique_lock guard(mutex);
		integer++;
	}} };

	std::jthread t2{ [&] {for (int i = 0; i < length; i++) {
		unique_lock guard(mutex);
		integer++;
	}} };

	t1.join(); t2.join();
	std::cout << "[INTEGER]\tExpected {" << length * 2 << "}, received {" << integer << "}\n";

}

#include <ranges>
#include <syncstream>
#include "Complex.h"
void OWN_thread_pool() {
	ThreadPool tp;

	auto print_item		= [&] (auto item) {std::osyncstream(std::cout) << item << "\n";};
	auto task			= [&] {std::ranges::for_each(std::ranges::iota_view{ 1,1'000 }, print_item);};
	auto emplace_task	= [&] (auto) {tp.emplace(task);};
	auto emplace_tasks	= [&] {std::ranges::for_each(std::ranges::iota_view{ 1,1'0 },emplace_task);};

	emplace_tasks();


	while (true);
}

int main() {
	OWN_thread_pool();


}
