#include "MenuScreen.h"
#include <iostream>

void MenuScreen::createButtons()
{
	sf::Vector2f midVec = sf::Vector2f(screenWidth / 2, screenHeight / 2);
	playButton = new Button(sf::String("Play"), midVec, sf::Color(0, 255, 0));
	playButton->setCallback([]() {std::cout << "I HAVE AIDS\n";});

	buttons.push_back(playButton);

	midVec.y -= 100;
	nameButton = new InputButton(sf::String("NAME: "), midVec, sf::Color(177, 177, 177));
	buttons.push_back(nameButton);
}

MenuScreen::MenuScreen(sf::RenderWindow *win)
    : Screen(win)
{
	titleFont = new sf::Font();
	if (!titleFont->loadFromFile("../resources/Pixel_Font.ttf")) {
		std::cout << "FAILED TO LOAD TITLE FONT" << std::endl;
	}
	title = sf::Text(sf::String("BlockPlanet"), *titleFont, 100);
	float titleX = (screenWidth / 2) - (title.getLocalBounds().getSize().x / 2);
	title.setFillColor(sf::Color::White);
	title.setPosition(sf::Vector2f(titleX, 0));

	createButtons();
}

MenuScreen::~MenuScreen()
{
	delete titleFont;
}

void MenuScreen::draw()
{
	window->clear();
	window->draw(title);
	for (Button* b : buttons) {
		b->draw(window);
	}
	window->display();
}

void MenuScreen::handleButtons(sf::Event event)
{
	Screen::handleButtons(event);
}
