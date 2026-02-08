#pragma once
#include <iostream>

struct ShapePrototype
{
	virtual ShapePrototype* clone() = 0;
};

struct Shape : ShapePrototype
{
private:
	float pos_x, pos_y;
	float r, g, b;

public:
	Shape()
	{
		pos_x = 0;	pos_y = 0;
		r = 1; g = 1; b = 0;
	}

	Shape(Shape& shape)
		: Shape()
	{
		this->pos_x = shape.pos_x;
		this->pos_y = shape.pos_y;
		this->r = shape.r;
		this->g = shape.g;
		this->b = shape.b;
	}


	virtual void Print()
	{
		std::cout << "Position: " << pos_x << "," << pos_y << "\nColor: " <<
			r << " " << g << " " << b << "\n";
	}

	void setR(float value) { r = value; };
};

struct Rectangle : Shape
{
	float size_x, size_y;

	Rectangle()
		: Shape()
	{
		size_x = 4;
		size_y = 2;
	}
	Rectangle(Rectangle& other)
		: Shape(other)
	{
		size_x = other.size_x;
		size_y = other.size_y;
	}

	Shape* clone() override
	{
		return new Rectangle(*this);
	}

	virtual void Print()
	{
		Shape::Print();
		std::cout << "Size: " << size_x << ", " << size_y << "\n";
	}
};



void PerformPrototype()
{
	Rectangle r;
	r.size_x = 400;
	r.size_y = 20;
	r.setR(55);
	r.Print();
	Rectangle* b = (Rectangle*)r.clone();
	b->Print();
}