/*
	1. Napisać joining_thread;
	2. Napisz przykład z data race i potem go rozwiąż
	3. Napisz przykład z deadlock i potem go rozwiąż
	4. Napisz spinlock.
	5. Napisz unique_lock.
*/

#include <thread>

class jthread
{
private:
	std::thread thread;

public:
	explicit jthread(std::thread t) : thread(std::move(t)) {}
	template <typename Callable, typename... Args> explicit jthread(Callable&& f, Args&&... args) 
		: thread(std::forward<Callable>(f), std::forward<Args>(args)...) {}
	~jthread() {
		if (thread.joinable()) {
			thread.join();
		}
	}
};

class spinlock
{
	std::atomic_flag flag;

public:
	void lock() {
		while (flag.test_and_set());
	}

	void unlock() {
		flag.clear();
	}
};

class unique_lock
{
	std::mutex* mutex{nullptr};
	std::atomic<bool> owning{false};
public:
	unique_lock() = default;
	unique_lock(std::mutex& m, std::adopt_lock_t = std::adopt_lock_t{}) : mutex(&m) {
		owning.store(true);
		mutex->lock();
	};
	unique_lock(std::mutex& m, std::defer_lock_t) : mutex(&m) {};

	~unique_lock() { 
		if(owning.load())
			mutex->unlock();
	}

	unique_lock& operator=(std::mutex m) {
		if (owning.load()) mutex->unlock();
		
		owning.store(true);
		mutex = &m;

	}

	void release() {
		mutex = nullptr;
		owning.store(false);
	}

	void lock() {
		mutex->lock();
	}

	void unlock() {
		mutex->unlock();
	}
};