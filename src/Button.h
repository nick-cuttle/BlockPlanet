#pragma once
#ifndef BUTTON_HPP
#define BUTTON_HPP
#include <SFML/Graphics.hpp>
#include <SFML/Window/Mouse.hpp>
#include <memory>
class Button
{
protected:

	sf::Text text;
	sf::RectangleShape box;
	void(*onCallback)();
	sf::Color color;
	sf::Font* font;

public:
	Button();
	virtual ~Button();

    Button(Button &&other);
	Button& operator=(Button&& other);

	Button(const Button& other);
	Button &operator=(const Button &other);

    Button(const sf::String text, sf::Vector2f pos);
    Button(const sf::String text, sf::Vector2f pos, sf::Color color);
	
	virtual void onEvent(sf::Event event);
	void draw(sf::RenderWindow* window);
	void setCallback( void(*callback)() );
	void setColor(sf::Color c) {
		color = c;
		box.setFillColor(color);
	}
};
#endif


