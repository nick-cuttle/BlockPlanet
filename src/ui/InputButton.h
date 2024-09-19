#pragma once
#ifndef INPUTBUTTON_H
#define INPUTBUTTON_H

#include "Button.h"


class InputButton: public Button
{
private:

    bool isActive;
    sf::Text label;

public:
    InputButton();
    ~InputButton();
    InputButton(const sf::String text, sf::Vector2f pos);
    InputButton(const sf::String text, sf::Vector2f pos, sf::Color color, sf::String label);
    void onEvent(sf::Event event);

    virtual void draw(sf::RenderWindow* window);

    InputButton(InputButton &&other);
    InputButton & operator=(InputButton && other);

    InputButton(const InputButton &other);
    InputButton &operator=(const InputButton &other);
};
#endif

