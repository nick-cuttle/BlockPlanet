#include "Block.hpp"
#include <string>
#include <iostream>
#include "../Config.hpp"
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

void Block::draw(sf::RenderWindow* win)
{
    win->draw(sprite);
}

// //update the sprite's position based on the player's position
// void Block::updatePosition(const sf::Vector2f& playerPos) {

//     // float screenX = (pos.x - playerPos.x) * Block::SIZE + (Config::SCREEN_SIZE.width / 2);
//     // float screenY = (playerPos.y - pos.y) * Block::SIZE + (Config::SCREEN_SIZE.height / 2);
//     //(-1 * pos.y - playerPos.y) * (-1 * Block::SIZE) + (Config::SCREEN_SIZE.height / 2);


//     float screenX = (pos.x * Block::SIZE  - playerPos.x * Block::SIZE) + (Config::SCREEN_SIZE.width / 2);
//     float screenY = (playerPos.y * Block::SIZE - pos.y * Block::SIZE) + (Config::SCREEN_SIZE.height / 2);
//     sprite.setPosition(screenX, screenY);
// }

void Block::updatePosition(const sf::Vector2f& playerPos) {
    // Scale the player's position and the block's position by Block::SIZE to ensure they match the world scale.
    float scaledPlayerX = playerPos.x;
    float scaledPlayerY = playerPos.y;
    float scaledBlockX = pos.x * Block::SIZE;
    float scaledBlockY = pos.y * Block::SIZE;

    // Calculate the screen position based on the difference between the block's position and the player's position.
    float screenX = (scaledBlockX - scaledPlayerX) + (Config::SCREEN_SIZE.width / 2);
    float screenY = (scaledPlayerY - scaledBlockY) + (Config::SCREEN_SIZE.height / 2);

    // Set the block's sprite position on the screen
    sprite.setPosition(screenX, screenY);
}
