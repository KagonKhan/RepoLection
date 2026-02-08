#pragma once
#include <condition_variable>
#include <unordered_map>
#include <list>
#include <Queue>
#include <mutex>

// ============================ QUEUE ============================
template <typename T>
class SafeQueue {
private:
	std::queue<std::shared_ptr<T>> queue;
	std::mutex lock;

public:
	void push(T item) {
		auto shared_item = std::make_shared<T>(std::move(item));
		std::lock_guard guard(lock);
		queue.push(std::move(shared_item));
	}

	std::shared_ptr<T> pop() {
		std::lock_guard guard(lock);
		if (queue.empty()) return nullptr;
		auto item{ std::move(queue.front()) };
		queue.pop();
		return item;
	}

	bool try_pop(std::shared_ptr<T>& result) {
		std::lock_guard guard(lock);
		if (queue.empty()) return false;
		result = queue.front();
		queue.pop();
		return true;
	}

	bool empty() {
		std::lock_guard guard(lock);
		return queue.empty();
	}
};

template <typename T>
class WaitingSafeQueue {
private:
	std::queue<std::shared_ptr<T>> queue;
	std::mutex lock;
	std::condition_variable data_pushed;

public:
	void push(T item) {
		auto shared_item = std::make_shared<T>(std::move(item));
		std::lock_guard guard(lock);
		queue.push(std::move(shared_item));
		data_pushed.notify_one();
	}

	std::shared_ptr<T> pop() {
		std::lock_guard guard(lock);
		if (queue.empty()) return nullptr;
		auto item{ std::move(queue.front()) };
		queue.pop();
		return item;
	}

	bool try_pop(std::shared_ptr<T>& result) {
		std::lock_guard guard(lock);
		if (queue.empty()) return false;
		result = queue.front();
		queue.pop();
		return true;
	}

	void wait_pop(std::shared_ptr<T>& result) {
		std::lock_guard guard(lock);
		data_pushed.wait(guard, [this] {return !queue.empty(); });
		result = queue.front();
		queue.pop();
		return true;
	}

	std::shared_ptr<T> wait_pop() {
		std::unique_lock lk(lock);
		data_pushed.wait(lk, [&]{return !queue.empty(); });
		auto item{ std::move(queue.front()) };
		queue.pop();
		return item;
	}

	bool empty() {
		std::lock_guard guard(lock);
		return queue.empty();
	}
};


// ============================ LIST ============================
template <typename T>
class SafeList {
private:
	using SharedT = std::shared_ptr<T>;
	std::list<SharedT> list;
	std::mutex lock;

public:
	void push(T item) {
		auto shared_item = std::make_shared<T>(std::move(item));
		std::lock_guard guard(lock);
		list.push_back(std::move(shared_item));
	}
	
	SharedT pop_front() {
		std::lock_guard guard(lock);
		auto item{ list.front() };
		list.pop_front();
		return item;
	}

	bool empty() {
		std::lock_guard guard(lock);
		return list.empty();
	}
};


// ============================ MAP ============================
template <typename T>
class SafeMap {
private:
	std::unordered_map<T, std::shared_ptr<T>> map;
	std::mutex lock;

public:
	void push(T item) {
		auto shared_item = std::make_shared<T>(std::move(item));
		std::lock_guard guard(lock);
		map.emplace(item, std::move(shared_item));
	}


	bool empty() {
		std::lock_guard guard(lock);
		return map.empty();
	}
};