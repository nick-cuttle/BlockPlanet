#include "MenuScreen.h"
#include <iostream>


MenuScreen::MenuScreen(sf::RenderWindow* win)
	:Screen(win)
{
	this->playButton = Button(sf::String("Play"), sf::Vector2f(screenWidth / 2, screenHeight / 2), sf::Vector2f(100, 50));
	playButton.setColor(sf::Color::Green);
	playButton.setCallback([]() {std::cout << "I HAVE AIDS\n";});
	buttons.push_back(playButton);
}

void MenuScreen::draw()
{
	window->clear();
	for (Button& b : buttons) {
		b.draw(window);
	}
	window->display();
}

void MenuScreen::handleButtons()
{
}
