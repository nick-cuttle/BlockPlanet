#include "Player.hpp"
#include "Config.hpp"

sf::Vector2f Player::PLAYER_SIZE = sf::Vector2f(50, 100);
double Player::PLAYER_SPEED = 10;

Player::Player()
	: Entity(sf::Vector2f(0, 0), PLAYER_SPEED, PLAYER_SIZE)
{
	sf::VideoMode vm = sf::VideoMode::getDesktopMode();
	model.setPosition(vm.width / 2, vm.height / 2);
	this->name = "DEFAULT";
	this->index = -1;
	this->hasMoved = false;
}

Player::Player(std::string name, sf::Vector2f pos)
	: Entity(pos, PLAYER_SPEED, PLAYER_SIZE)
{
	sf::VideoMode vm = sf::VideoMode::getDesktopMode();
	model.setPosition(vm.width / 2, vm.height / 2);
	this->name = name;
	this->index = -1;
	this->hasMoved = false;
}

void Player::move() {
	hasMoved = false;
	double moveSpeed{ PLAYER_SPEED };
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
		moveSpeed = moveSpeed * 2;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		position.y += moveSpeed;
		hasMoved = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		position.x -= moveSpeed;
		hasMoved = true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		position.y -= moveSpeed;
		hasMoved = true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		position.x += moveSpeed;
		hasMoved = true;
	}


	//model.setPosition(position);
	/*if (hasMoved) {
		sf::Packet p;
		p << Config::PacketType::PLAYER_POS << position.x << position.y;
		client->sendPacket(p);
		PENIS
	}*/
}

void Player::update() {
	move();
	
}

void Player::draw(sf::RenderWindow& window) {
	Entity::draw(window);
}

std::string Player::getName() {
	return name;
}

sf::Uint8 Player::getIndex() {
	return index;
}

void Player::setIndex(sf::Uint8 i) {
	index = i;
}

bool Player::getHasMoved() {
	return hasMoved;
}

void Player::setHasMoved(bool b) {
	hasMoved = b;
}



	
