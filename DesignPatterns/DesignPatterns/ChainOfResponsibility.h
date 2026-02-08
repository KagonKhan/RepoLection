#include <iostream>
namespace ChainOfResponsibility
{
	class RequestHandler
	{
	public:
		virtual float handle(float radius) = 0;
		virtual RequestHandler* setNext(RequestHandler* next) = 0;
	};

	class SphereAreaCalculator : public RequestHandler
	{
	public:
		float handle(float radius) override {
			if (radius < 0.f)
				return 0.f;

			if (next) return next->handle(radius);
		}

		RequestHandler* setNext(RequestHandler* next) override {
			this->next = next;
			return next;
		}
	protected:
		RequestHandler* next{ nullptr };
	};

	class Scalar : public SphereAreaCalculator
	{
	public:
		Scalar(float scale) : scale(scale) {}

		float handle(float radius) override {
			if (next)
				return next->handle(scale * radius);
			else
				return (scale * radius);
		}
	private:
		float scale{ 0.f };
	};

	class Multiplier : public SphereAreaCalculator
	{
	public:
		Multiplier(float multiply) : multiply(multiply) {}

		float handle(float radius) override {
			if (next)
				return next->handle(multiply * radius);
			else
				return (multiply * radius);
		}
	private:
		float multiply{ 0.f };
	};

	class Squarer : public SphereAreaCalculator
	{
	public:
		float handle(float radius) override {
			if (next)
				return next->handle(radius * radius);
			else
				return (radius * radius);
		}
	};

}

void performChainOfResponsibility()
{
	using namespace ChainOfResponsibility;

	SphereAreaCalculator calculator;
	Squarer square;
	Multiplier multiply{ 3.14159f };
	Scalar scale{ 4.f };
	calculator.setNext(&square)->setNext(&multiply)->setNext(&scale);

	std::cout << "Area of a sphere with radius{5}: " << calculator.handle(5.f) << "\n";

}