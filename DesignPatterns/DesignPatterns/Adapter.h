#pragma once
#include <iostream>

struct Point2D
{
	int x, y;
};

struct Color3
{
	float r, g, b;
};

struct Shape
{
	Point2D top_left, top_right, bottom_right, bottom_left;
	Color3 color;
};


class MyPrettyInterface {
public:
	virtual void plot(Shape s) = 0;
};

class Ugly3rdPartyInterface
{
public:
	void plot(Point2D top_left, Point2D top_right, Point2D bottom_right, Point2D bottom_left, float r, float g, float b){};
};


class Adapter : public MyPrettyInterface
{
private:
	Ugly3rdPartyInterface* adapt;

public:
	Adapter(Ugly3rdPartyInterface* interface) {
		adapt = interface;
	}

	void plot(Shape s) override {
		adapt->plot(s.top_left, s.top_right, s.bottom_right, s.bottom_left, s.color.r, s.color.g, s.color.b);
	};
};



void performAdapter() {
	Adapter adapt(new Ugly3rdPartyInterface);

	adapt.plot({});
}