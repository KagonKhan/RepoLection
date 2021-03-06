#include "Layout.h"

void Layout::draw(sf::RenderTarget& target, sf::RenderStates) const
{
	for (auto&& widget : m_Widgets)
		target.draw(*widget.get());
}

Layout::Layout(float padding, opt_ref parent)
	: Widget(parent), m_Padding(padding)
{
	puts("Layout\t\tctor");
}

Layout::~Layout()
{
	puts("Layout\t\tdtor");
}

void Layout::processEvent(const sf::Event& sfevent)
{
	for (auto&& widget : m_Widgets)
		widget->processEvent(sfevent);
}

void Layout::add(std::unique_ptr<Widget> widget)
{
	m_Widgets.push_back(std::move(widget));
	updateShape();
}

Widget& Layout::getAt(unsigned int index) const
{
	return *m_Widgets.at(index).get();
}





void Layout::setPosition(const sf::Vector2f& pos)
{
	m_Position = pos;
	updateShape();
}

