#include "Block.hpp"
#include <string>
#include <iostream>
using namespace std;

Block::Block()
    :
    pos(0, 0)
{    
}

Block::Block(sf::Vector2i p)
    :
    pos(p)
{
    sprite.setPosition(pos.x, pos.y);
}

void Block::draw(sf::RenderWindow *win)
{
    win->draw(sprite);
}
