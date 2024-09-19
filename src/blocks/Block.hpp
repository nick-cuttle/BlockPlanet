
#pragma once
#include <SFML/Graphics.hpp>
#include "../TexureManager.hpp"

class GrassBlock;

class Block {

public:

public:

protected:

    sf::Vector2i pos;
    sf::Sprite sprite;

private:

    

public:

    Block();
    Block(sf::Vector2i pos);

    virtual void draw(sf::RenderWindow* win);
 
};