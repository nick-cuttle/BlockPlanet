#pragma once
#ifndef BUTTON_HPP
#define BUTTON_HPP
#include <SFML/Graphics.hpp>
#include <SFML/Window/Mouse.hpp>
class Button
{
private:

	sf::Text text;
	sf::RectangleShape box;
	void(*onCallback)();
	sf::Color color;
	sf::Font* font;

public:
	Button();
	~Button();
	Button(const sf::String text, sf::Vector2f pos, sf::Vector2f size);
	void onClick();
	void draw(sf::RenderWindow* window);
	void setCallback( void(*callback)() );
	void setColor(sf::Color c) {
		color = c;
		box.setFillColor(color);
	}
};
#endif

