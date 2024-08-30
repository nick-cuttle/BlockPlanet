#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <string>
#include <SFML/System.hpp>
#include <iostream>

namespace Config {

	enum GameState : sf::Uint8 {
		MENU,
		SETTINGS,
		RUNNING
	};
 
	extern GameState gameState;
	const unsigned short SERVER_PORT = 2525;
	const std::string SERVER_IP{ "localhost" };
	
	enum PacketType : sf::Uint8 {
		PLAYER_JOIN,
		PLAYER_MOVED
	};

}


#endif