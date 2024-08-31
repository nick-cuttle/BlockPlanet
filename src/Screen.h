#pragma once
#ifndef SCREEN_HPP
#define SCREEP_HPP

#include <SFML/Graphics.hpp>
#include "Button.h"
#include "Config.hpp"

class Screen
{
private:

protected:
	sf::RenderWindow* window;
	std::vector<Button*> buttons;
	unsigned int screenWidth;
	unsigned int screenHeight;

public:

	Screen(sf::RenderWindow* win) {
		this->window = win;

		sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
		this->screenWidth = desktopMode.width;
		this->screenHeight = desktopMode.height;
	}

	virtual void draw() = 0;
	virtual void handleButtons(sf::Event event) = 0;

	std::vector<Button*>& getButtons() {
		return buttons;
	}
	void setButtons(std::vector<Button*>& b) {
		buttons = b;
	}

};
#endif

