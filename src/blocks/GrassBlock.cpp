#include "GrassBlock.hpp"

GrassBlock::GrassBlock()
    :
    Block()
{
}

GrassBlock::GrassBlock(sf::Vector2i p)
    :
    Block(p)
{
    sprite.setTexture(TextureManager::GrassBlockTexture);
}


