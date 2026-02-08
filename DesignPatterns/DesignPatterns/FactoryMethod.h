#pragma once
#include <iostream>

struct Type1;
struct Ship
{

public:
	virtual void WhatAmI() = 0;

	enum class ShipTypes{ Type1, Type2, Type3, Type4, Type5 };

};


struct Type1 : public Ship
{
	void WhatAmI() override
	{
		std::cout << "I am Type 1!\n";
	}
};
struct Type2 : Ship
{
	void WhatAmI() override
	{
		std::cout << "I am Type 2!\n";
	}
};
struct Type3 : Ship
{
	void WhatAmI() override
	{
		std::cout << "I am Type 3!\n";
	}
};
struct Type4 : Ship
{
	void WhatAmI() override
	{
		std::cout << "I am Type 4!\n";
	}
};
struct Type5 : Ship
{
	void WhatAmI() override
	{
		std::cout << "I am Type 5!\n";
	}
};


Ship* MakeShip(Ship::ShipTypes type)
{
	switch (type)
	{
	case Ship::ShipTypes::Type1: return new Type1; break;
	case Ship::ShipTypes::Type2: return new Type2; break;
	case Ship::ShipTypes::Type3: return new Type3; break;
	case Ship::ShipTypes::Type4: return new Type4; break;
	case Ship::ShipTypes::Type5: return new Type5; break;
	default:									   break;
	}
}



void PerformFactoryMethod()
{
	std::unique_ptr<Ship> ship{ MakeShip(Ship::ShipTypes::Type2) };

	ship->WhatAmI();
}