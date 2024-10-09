#include "Config.hpp"
using GameState = Config::GameState;

GameState Config::gameState = GameState::MENU;

sf::VideoMode Config::SCREEN_SIZE = sf::VideoMode::getDesktopMode();