#include "stdafx.h"
#include "EditorState.h"

//Initializers
void EditorState::initBackgrounds() {

}
void EditorState::initVariables() {

}
void EditorState::initFonts() {
	if (this->font.loadFromFile("Fonts/Dosis-Light.otf")) {
		//	throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
	}

}

void EditorState::initKeybinds() {

	std::ifstream ifs("Config/editorstate_keybinds.ini");

	if (ifs.is_open()) {
		std::string key = "", key2 = "";
		while (ifs >> key >> key2)
			this->keybinds[key] = this->supportedKeys->at(key2);
	}
	ifs.close();
}

void EditorState::initButtons() {

}

EditorState::EditorState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	:State(window, supportedKeys, states) {

	this->initVariables();
	this->initBackgrounds();
	this->initFonts();
	this->initKeybinds();
	this->initButtons();

}


EditorState::~EditorState() {
	auto it = this->buttons.begin();
	for (it; it != buttons.end(); ++it) {
		delete it->second;
	}
}



void EditorState::updateInput(const float& dt) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))))
		this->endState(); 
}

void EditorState::updateButtons() {

	/*Updates buttons in the state and handles functionality*/

	for (auto it : this->buttons)
		it.second->update(this->mousePosView);

}

void EditorState::update(const float& dt) {
	this->updateMousePositions();
	this->updateInput(dt);

	this->updateButtons();



}

void EditorState::renderButtons(sf::RenderTarget& target) {
	for (auto it : this->buttons)
		it.second->render(target);

}

void EditorState::render(sf::RenderTarget* target) {
	if (!target)
		target = this->window;

	this->renderButtons(*target);

}
