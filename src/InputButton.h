#pragma once
#ifndef INPUTBUTTON_H
#define INPUTBUTTON_H

#include "Button.h"


class InputButton: public Button
{
private:

    bool isActive;

public:
    InputButton();
    ~InputButton();
    InputButton(const sf::String text, sf::Vector2f pos);
    InputButton(const sf::String text, sf::Vector2f pos, sf::Color color);
    void onEvent(sf::Event event);

    InputButton(InputButton &&other);
    InputButton & operator=(InputButton && other);

    InputButton(const InputButton &other);
    InputButton &operator=(const InputButton &other);
};
#endif

