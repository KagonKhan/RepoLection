#pragma once


#include "gui.h"

class PauseMenu
{

private:
	sf::RectangleShape background;
	sf::RectangleShape container;
	sf::Font& font;
	sf::Text menuText;
	
	std::map<std::string, gui::Button*> buttons;

public:
	PauseMenu(sf::RenderWindow& window, sf::Font& font);
	virtual ~PauseMenu();


	//Accessors
	std::map<std::string, gui::Button*>& getButtons();

	//Functions
	const bool isButtonPressed(const std::string& key);

	void addButton(const std::string& key, float y, const std::string& text);
	void update(const sf::Vector2f& mousePos);
	void render(sf::RenderTarget& target);

};

