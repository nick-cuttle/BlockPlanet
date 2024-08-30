#include "Button.h"
#include <iostream>

Button::~Button() {
	//delete font;
}

Button::Button() {
	font = new sf::Font();
	font->loadFromFile("../resources/Pixel_Font.ttf");
	this->text = sf::Text("", *font);
	this->box = sf::RectangleShape(sf::Vector2f(100, 50));
	this->onCallback = nullptr;
}

Button::Button(sf::String text, sf::Vector2f pos, sf::Vector2f size)
{

	font = new sf::Font();
	if (!font->loadFromFile("../resources/Pixel_Font.ttf")) {
		std::cout << "FAILED TO LOAD FONT" << std::endl;
	};
	this->text = sf::Text(text, *font);
	this->text.setPosition(pos);
	this->text.setCharacterSize(36);
	this->text.setStyle(sf::Text::Regular);

	this->box = sf::RectangleShape(size);
	this->box.setPosition(pos);
	this->onCallback = nullptr;
	this->color = sf::Color::White;

}

void Button::draw(sf::RenderWindow* window) {
	//window->draw(box);
	window->draw(text);
}

void Button::setCallback(void(*callback)()) {
	onCallback = callback;
}

void Button::onClick() {
	sf::FloatRect boxBound{ box.getGlobalBounds() };
	sf::Vector2f mousePos{ sf::Mouse::getPosition() };

	//check whether clicked.
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && boxBound.contains(mousePos)) {
		onCallback();
	}
	
	
}
