#include <iostream>
#include <vector>

class Subscriber
{
public:
	virtual void update(const std::string& message) = 0;
};

class Publisher
{
	std::vector<Subscriber*> subs;

public:
	void addSubscriber(Subscriber* sub) { subs.push_back(sub); }
	void removeSubscriber(Subscriber* sub) {
		std::erase_if(subs, [sub](Subscriber* subber) {
				return subber == sub;
			});
	}

	void changeMe(const std::string& update) {
		for (auto& sub : subs)
			sub->update(update);
	};
};

class Subber : public Subscriber
{
public:

	void update(const std::string& message) override {
		std::cout << message << "\n";
	}
};


void performObserver() {
	Subber sub1, sub2, sub3, sub4;

	Publisher publisher;
	publisher.addSubscriber(&sub1);
	publisher.addSubscriber(&sub2);
	publisher.addSubscriber(&sub3);
	publisher.addSubscriber(&sub4);

	publisher.changeMe("oh no I'm dying. Tell my kids I love them\n");

	publisher.removeSubscriber(&sub2);
	publisher.changeMe("nevermind I'm fine :)\n");


}