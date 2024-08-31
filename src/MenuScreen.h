#pragma once
#ifndef MENU_SCREEN_HPP
#define MENU_SCREEN_HPP

#include "Screen.h"
#include "Button.h"
#include "InputButton.h"

class MenuScreen : public Screen

{

private:

	sf::Text title;
	sf::Font* titleFont;
	InputButton* nameButton;
	Button* playButton;
	void createButtons();

public:
	// Inherited via Screen
	MenuScreen(sf::RenderWindow* win);
	~MenuScreen();

	void draw() override;
	void handleButtons(sf::Event event) override;
};
#endif

