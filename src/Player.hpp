#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Entity.hpp"
#include <SFML/Network.hpp>

class Player : public Entity {

	static sf::Vector2f PLAYER_SIZE;
	static double PLAYER_SPEED;

private:
	std::string name;
	sf::Uint8 index;
	bool hasMoved;

public:

	Player();

	Player(std::string name, sf::Vector2f pos);

	void move() override;

	sf::Uint8 getIndex();

	bool getHasMoved();

	void setHasMoved(bool b);

	void setIndex(sf::Uint8 i);

	void update() override;

	void draw(sf::RenderWindow& window) override;

	std::string getName();

	void setName(std::string& name) {
		this->name = name;
	}

	// Serialization
	friend sf::Packet& operator << (sf::Packet& packet, const Player& player) {
		return packet << player.name << player.position.x << player.position.y << player.index;
	}

	// Deserialization
	friend sf::Packet& operator >> (sf::Packet& packet, Player& player) {
		packet >> player.name >> player.position.x >> player.position.y >> player.index;
		player.model.setPosition(player.position.x, player.position.y);
		return packet;
	}


	
};

#endif