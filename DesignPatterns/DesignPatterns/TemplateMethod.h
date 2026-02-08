#include <iostream>

class CubeCalculator
{
	virtual void powerer() = 0;
	virtual void multiplier() = 0;

protected:
	float base{ 1.f };

public:
	float perform(float a) {
		base = a;

		powerer();
		multiplier();

		return base;
	};
};


class CubeVolumeCalculator : public CubeCalculator
{
	void powerer() override {
		base = std::pow(base, 3);
	};
	void multiplier() override {
		base *= 1;
	};
};

class CubeAreaCalculator : public CubeCalculator
{
	void powerer() override {
		base = std::pow(base, 2);
	};
	void multiplier() override {
		base *= 6;
	};
};


void performTemplateMethod()
{
	CubeAreaCalculator cac;
	CubeVolumeCalculator cvc;

	std::cout << "Cube area with a{5} = " << cac.perform(5);
	std::cout << "\nCube volume with a{5} = " << cvc.perform(5);
}