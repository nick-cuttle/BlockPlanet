#include "Entity.hpp"

Entity::Entity(sf::Vector2f pos)
{
	this->position = pos;
	this->speed = 0;
	this->size = sf::Vector2f(1, 1);
	this->model = sf::RectangleShape(size);
	model.setPosition(position);
}

Entity::Entity(sf::Vector2f pos, double speed)
	: Entity(pos)
{
	this->speed = speed;
	
}

Entity::Entity(sf::Vector2f pos, double speed, sf::Vector2f size) {
	this->position = pos;
	this->speed = speed;
	this->size = size;
	this->model = sf::RectangleShape(size);
	model.setPosition(position);
}

sf::Vector2f& Entity::getPosition() {
	return position;
}

void Entity::setPosition(sf::Vector2f& pos) {
	position = pos;
	model.setPosition(pos);
}

double Entity::getSpeed() const {
	return speed;
}

void Entity::setSpeed(double spd) {
	speed = spd;
}

sf::Vector2f& Entity::getSize() {
	return size;
}

void Entity::setSize(sf::Vector2f& s) {
	size = s;
}

void Entity::draw(sf::RenderWindow& window) {
	window.draw(model);
}
