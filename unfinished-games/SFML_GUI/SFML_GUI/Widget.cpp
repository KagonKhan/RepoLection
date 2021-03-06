#include "Widget.h"

Widget::Widget(opt_ref parent)
	: m_Parent(parent)
{
	m_Position = sf::Vector2f(0, 0);
	puts("Widget\t\tctor");
}
 
Widget::~Widget()
{
	puts("Widget\t\tdtor");
}

void Widget::processEvent(const sf::Event&)
{

}

void Widget::update(const sf::Time&)
{

}

void Widget::setPosition(float x, float y)
{
	setPosition(sf::Vector2f(x, y));
}

const sf::Vector2f& Widget::getPosition() const
{
	return m_Position;
}

void Widget::setParent(opt_ref parent)
{
	m_Parent = parent;
}
