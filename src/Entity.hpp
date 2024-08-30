#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SFML/Graphics.hpp> 

class Entity {
private:


protected:
	sf::Vector2f position;

	double speed;

	sf::Vector2f size;

	sf::RectangleShape model;

public:

	Entity() = default;

	Entity(sf::Vector2f pos);
	Entity(sf::Vector2f pos, double speed);
	Entity(sf::Vector2f pos, double speed, sf::Vector2f size);

	virtual void move() = 0;

	virtual void update() = 0;

	virtual void draw(sf::RenderWindow& window) = 0;

	sf::Vector2f& getPosition();

	void setPosition(sf::Vector2f& pos);

	double getSpeed() const;

	void setSpeed(double spd);

	sf::Vector2f& getSize();

	void setSize(sf::Vector2f& s);

	
};


#endif
