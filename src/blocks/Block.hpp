
#pragma once
#include <SFML/Graphics.hpp>
#include "../TexureManager.hpp"
#include <SFML/System/Vector2.hpp>

class Block {

private:


public:

    static constexpr float SIZE = 40.0f;


protected:

    sf::Vector2i pos;
    sf::Sprite sprite;

private:

    

public:

    Block();
    Block(sf::Vector2i pos);

    sf::Vector2i& getPosition() { return pos; }

    virtual void draw(sf::RenderWindow* win);

    void updatePosition(const sf::Vector2f& playerPos);
 
};