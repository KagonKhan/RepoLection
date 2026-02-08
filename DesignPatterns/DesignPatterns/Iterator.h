#include <iostream>

struct Point {
	float x, y;
};

class Iterator
{
public:
	virtual Point getNext() = 0;
	virtual bool hasMore() = 0;
};

class Iterable
{
public:
	virtual Iterator* createIterator() = 0;
};

class ForwardIterator;
class SmartContainer : public Iterable
{
	Point top_left{ 0,1 };
	Point top_right{ 1,1 };
	Point bot_right{ 1,0 };
	Point bot_left{ 0,0 };

	friend class ForwardIterator;

public:
	Iterator* createIterator() {
		return new ForwardIterator(this);
	}
};

class ForwardIterator : public Iterator
{
	std::size_t current_index{ 0 };
	SmartContainer* collection;
public:
	ForwardIterator(SmartContainer* collection) : collection{ collection } {

	}

	Point getNext() override {
		switch (current_index++)
		{
		case 0:			return collection->top_left;			break;
		case 1:			return collection->top_right;			break;
		case 2:			return collection->bot_right;			break;
		case 3:			return collection->bot_left;			break;

		default: // throw
			break;
		}
	}
	bool hasMore() override {
		return current_index < 4;
	}
};



void performIterator()
{
	SmartContainer s;

	for (auto it = s.createIterator(); it->hasMore(); ) {
		auto current = it->getNext();
		std::cout << "Point: " << current.x << ", " << current.y << "\n";
	}
}