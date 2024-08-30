#pragma once
#ifndef MENU_SCREEN_HPP
#define MENU_SCREEN_HPP

#include "Screen.h"
#include "Button.h"

class MenuScreen : public Screen

{

private:

	Button playButton;

public:
	// Inherited via Screen
	MenuScreen(sf::RenderWindow* win);

	void draw() override;
	void handleButtons() override;
};
#endif

