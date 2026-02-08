#include <thread>
#include <vector>
#include "ThreadSafeContainers.h"
#include <functional>


template <typename T>
class LockFreeList {
	LockFreeList(const LockFreeList& other) = delete;
	LockFreeList& operator=(const LockFreeList& other) = delete;

	struct node {
		std::shared_ptr<T> data{nullptr};
		node* next{nullptr};

		node(const T& new_data) : data(new_data) {}
	};

	std::atomic<node*> head{ new Node() }, tail{ new Node() };
	

public:
	void insert();
	void delete();
	void lookup();
};


class ThreadPool
{
	SafeQueue<std::function<void()>> work_queue;
	std::vector<std::jthread> workers;
	std::atomic<bool> finished{ false };
	
	void work() {
		while (!finished.load()) {
			std::shared_ptr<std::function<void()>> task;
			if (work_queue.try_pop(task)) {
				(*task)();
			}
			else {
				std::this_thread::yield();
			}
		}
	}

public:
	ThreadPool(unsigned int size = std::thread::hardware_concurrency()) {
		workers.reserve(size);
		for (int i = 0; i < amount; ++i) {
			workers.emplace_back(&ThreadPool::work, this);
		}

	}

	~ThreadPool() {
		finished.store(true);
	}

	template<typename Function>
	void emplace(Function&& f) {
		work_queue.push(std::function<void()>(f));
	}

};