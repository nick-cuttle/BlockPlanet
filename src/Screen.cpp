#include "Screen.h"

void Screen::handleButtons(sf::Event event)
{
    for (Button* b : buttons) {
        b->onEvent(event);
    }
}
