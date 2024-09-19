#pragma once
#ifndef MENU_SCREEN_HPP
#define MENU_SCREEN_HPP

#include "Screen.h"
#include "ui/Button.h"
#include "ui/InputButton.h"

class MenuScreen : public Screen

{

private:

	sf::Text title;
	sf::Font* titleFont;
	InputButton* nameButton;
	Button* playButton;
	void createButtons();
	// void testCallback();

public:
	// Inherited via Screen
	MenuScreen();
	MenuScreen(sf::RenderWindow* win);
	~MenuScreen();

	Button* getNameButton() {
		return nameButton;
	}

    void draw() override;
	void handleButtons(sf::Event event) override;
};
#endif

