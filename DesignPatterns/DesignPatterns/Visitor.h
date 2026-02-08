#include <iostream>
#include <array>

namespace Visitor
{
	class ConcreteComponentA;
	class ConcreteComponentB;

	class Visitor {
	public:
		virtual void VisitConcreteComponentA(const ConcreteComponentA* element) const = 0;
		virtual void VisitConcreteComponentB(const ConcreteComponentB* element) const = 0;
	};

	class Component {
	public:
		virtual ~Component() {}
		virtual void Accept(Visitor* visitor) const = 0;
	};

	class ConcreteComponentA : public Component {
	public:
		void Accept(Visitor* visitor) const override {
			visitor->VisitConcreteComponentA(this);
		}
		std::string ExclusiveMethodOfConcreteComponentA() const {
			return "A";
		}
	};

	class ConcreteComponentB : public Component {
	public:
		void Accept(Visitor* visitor) const override {
			visitor->VisitConcreteComponentB(this);
		}
		std::string SpecialMethodOfConcreteComponentB() const {
			return "B";
		}
	};

	class ConcreteVisitor1 : public Visitor {
	public:
		void VisitConcreteComponentA(const ConcreteComponentA* element) const override {
			std::cout << element->ExclusiveMethodOfConcreteComponentA() << " + ConcreteVisitor1\n";
		}

		void VisitConcreteComponentB(const ConcreteComponentB* element) const override {
			std::cout << element->SpecialMethodOfConcreteComponentB() << " + ConcreteVisitor1\n";
		}
	};

	class ConcreteVisitor2 : public Visitor {
	public:
		void VisitConcreteComponentA(const ConcreteComponentA* element) const override {
			std::cout << element->ExclusiveMethodOfConcreteComponentA() << " + ConcreteVisitor2\n";
		}
		void VisitConcreteComponentB(const ConcreteComponentB* element) const override {
			std::cout << element->SpecialMethodOfConcreteComponentB() << " + ConcreteVisitor2\n";
		}
	};
}


void performVisitor()
{
	using namespace Visitor;
	std::array<std::unique_ptr<Component>, 2> components = {
		std::make_unique<ConcreteComponentA>(), std::make_unique<ConcreteComponentB>()
	};
	
	auto visitor1 = std::make_unique<ConcreteVisitor1>();

	for (auto&& comp : components) {
		comp->Accept(visitor1.get());
	}

}