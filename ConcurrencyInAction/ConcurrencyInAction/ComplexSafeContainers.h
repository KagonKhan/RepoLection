#include <memory>
#include <mutex>

template <typename T> 
class FineSafeQueue {
private:
	struct Node {
		std::shared_ptr<T> data;
		Node* next;
	};

	Node* head;
	std::mutex head_mutex, tail_mutex;
	Node* tail;

	Node* getTail() {
		std::lock_guard tail_lock{ tail_mutex };
		return tail;
	}

	Node* popHead() {
		std::lock_guard head_lock{ head_mutex };

		if (head == getTail()) {
			return nullptr;
		}

		auto old = std::move(head);
		head = std::exchange(old->next, nullptr);
		return old;
	}
	std::condition_variable data_cond;

	FineSafeQueue(const FineSafeQueue<T>&) = delete;
	FineSafeQueue<T>& operator=(const FineSafeQueue&) = delete;

public:
	FineSafeQueue() : head(new Node), tail(head) {}


	std::shared_ptr<T> try_pop() {
		auto old{ popHead() };
		return old ? old->data : nullptr;
	}
	
	bool try_pop(T& value);

	std::shared_ptr<T> wait_and_pop();
	void wait_and_pop(T& value);

	void push(T item) {
		auto shared_item{ std::make_shared<T>(std::move(item)) };
		Node* new_node = new Node();
		Node* new_tail = new_node;

		std::lock_guard tail_lock(tail_mutex);
		tail->data = shared_item;
		tail->next = std::move(new_node);
		tail = new_tail;
	};
	
	bool empty() noexcept {
		std::lock_guard head_lock{ head_mutex };
		return head != nullptr;
	}
};