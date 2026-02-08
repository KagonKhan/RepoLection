#pragma once
#include "iostream"

class Item
{
public:
	virtual ~Item() {};
	virtual std::string operation() = 0;
};

class ConcreteItem : public Item {
public:
	std::string operation() override {
		return "item";
	}
};

class Decorator : public Item
{
private:
	Item* wrapped{ nullptr };

public:
	Decorator(Item* item) : wrapped{ item } {

	}

	std::string operation() override {
		return wrapped->operation();
	}
};

class A : public Decorator
{
public:
	A(Item* item) : Decorator{ item } {	}

	std::string operation() override {
		return "A(" + Decorator::operation() + ")";
	}
};

class B : public Decorator
{
public:
	B(Item* item) : Decorator{ item } {	}

	std::string operation() override {
		return "B(" + Decorator::operation() + ")";
	}
};

class C : public Decorator
{
public:
	C(Item* item) : Decorator{ item } {	}

	std::string operation() override {
		return "C(" + Decorator::operation() + ")";
	}
};

class D : public Decorator
{
public:
	D(Item* item) : Decorator{ item } {	}

	std::string operation() override {
		return "D(" + Decorator::operation() + ")";
	}
};


void performDecorator()
{
	ConcreteItem item;
	D d{ &item };
	A a{ &d };
	D D{ &a };
	A A{ &D };

	 std::cout << A.operation() << "\n";
}