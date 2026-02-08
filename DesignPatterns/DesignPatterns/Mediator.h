#include <iostream>


namespace Mediator {
	class BaseComponent;
	class Mediator
	{
	public:
		virtual void Notify(BaseComponent* sender, std::string event) const = 0;
	};

	class BaseComponent
	{
	protected:
		Mediator* mediator;

	public:
		BaseComponent(Mediator* mediator = nullptr) : mediator(mediator) { }
		void set_mediator(Mediator* mediator) {
			this->mediator = mediator;
		}
	};

	class Component1 : public BaseComponent {
	public:
		void DoA() {
			std::cout << "Component 1 does A.\n";
			mediator->Notify(this, "A");
		}
		void DoB() {
			std::cout << "Component 1 does B.\n";
			mediator->Notify(this, "B");
		}
	};
	class Component2 : public BaseComponent {
	public:
		void DoC() {
			std::cout << "Component 2 does C.\n";
			mediator->Notify(this, "C");
		}
		void DoD() {
			std::cout << "Component 2 does D.\n";
			mediator->Notify(this, "D");
		}
	};

	class ConcreteMediator : public Mediator
	{
		Component1* c1;
		Component2* c2;

	public:
		ConcreteMediator(Component1* c1, Component2* c2)
			: c1(c1), c2(c2) {
			c1->set_mediator(this);
			c2->set_mediator(this);
		}

		void Notify(BaseComponent* sender, std::string event) const override {
			if (event == "A") {
				std::cout << "Mediator reacts on A and triggers following operations:\n";
				this->c2->DoC();
			}
			if (event == "D") {
				std::cout << "Mediator reacts on D and triggers following operations:\n";
				this->c1->DoB();
				this->c2->DoC();
			}
		}
	};
}

void performMediator()
{
	using namespace Mediator;

	Component1 c1;
	Component2 c2;

	ConcreteMediator m{&c1, &c2};

	c1.DoA();

}