#include "Button.h"
#include <iostream>

Button::~Button() {
	delete font;
}

Button::Button(Button&& other)
    : text(std::move(other.text)),
      box(std::move(other.box)),
      onCallback(other.onCallback),
      color(other.color)
{
	font = other.font;
	text.setFont(*font);
	other.font = nullptr; //ensure other pointer invalided when it goes out of scope.
    other.onCallback = nullptr;
}

Button& Button::operator=(Button&& other) {
    if (this != &other) {
        text = std::move(other.text);
        box = std::move(other.box);
        onCallback = other.onCallback;
        color = other.color;
		font = other.font;
        text.setFont(*font);
		other.font = nullptr; //ensure other pointer invalided when it goes out of scope.
        setColor(color);
        other.onCallback = nullptr;
    }
    return *this;
}

//copy constructor (need to be careful)
Button::Button(const Button &other)
{
	if (this != &other) {

        this->text = other.text;
        this->box = other.box;
        this->onCallback = other.onCallback;
        this->color = other.color;
        setColor(color);
		font = other.font;

    }
}

//copy operator (need to be careful)
Button &Button::operator=(const Button &other)
{
    if (this != &other) {

        this->text = other.text;
        this->box = other.box;
        this->onCallback = other.onCallback;
        this->color = other.color;
        setColor(color);
		font = other.font;

    }
    return *this;
}

Button::Button() {
	font = new sf::Font();
	font->loadFromFile("../resources/Pixel_Font.ttf");
	this->text = sf::Text("", *font);
	this->box = sf::RectangleShape(sf::Vector2f(100, 50));
	this->onCallback = nullptr;
	setColor(sf::Color::White);
}

Button::Button(sf::String text, sf::Vector2f pos)
{
	font = new sf::Font();
	if (!font->loadFromFile("../resources/Pixel_Font.ttf")) {
		std::cout << "FAILED TO LOAD FONT" << std::endl;
	};
	this->text = sf::Text(text, *font, 48);

	sf::FloatRect localBounds {this->text.getLocalBounds()};
	float dx = localBounds.getSize().x / 2;
	float dy = localBounds.getSize().y / 2;
	
	sf::Vector2f centered{pos.x - dx, pos.y - dy};
	this->text.setPosition(centered);

	localBounds = this->text.getLocalBounds();

	this->box = sf::RectangleShape(localBounds.getSize());
	// Adjust the position of the box to match the text
	const sf::Vector2f& textPos = this->text.getPosition();
    this->box.setPosition(textPos.x + localBounds.left, textPos.y + localBounds.top);

	this->onCallback = nullptr;
	setColor(sf::Color::White);

}

Button::Button(const sf::String text, sf::Vector2f pos, sf::Color color)
	: Button(text, pos)
{
	setColor(color);
}

void Button::draw(sf::RenderWindow* window) {
	window->draw(box);
	window->draw(text);
}

void Button::setCallback(void(*callback)()) {
	onCallback = callback;
}

void Button::onEvent(sf::Event event) {
	sf::FloatRect boxBound{ box.getGlobalBounds() };
	sf::Vector2f mousePos{ sf::Mouse::getPosition() };

	if (event.type == sf::Event::MouseButtonPressed) {
		if (event.mouseButton.button == sf::Mouse::Left && boxBound.contains(mousePos)) {
			onCallback();
		}
	}	
}
