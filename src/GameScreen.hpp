#ifndef GAMESCREEN_HPP
#define GAMESCREEN_HPP

#include "Screen.h"
#include "Player.hpp"

class GameScreen : public Screen {

private:

    std::vector<Player>* players;


public:

    GameScreen() = default;
    GameScreen(sf::RenderWindow* win, std::vector<Player>* plys)
        :
        Screen(win),
        players(plys)
    {
    }

    void draw();
	void handleButtons(sf::Event event);

    void setPlayers(std::vector<Player>* players) {
        this->players = players;
    }



};






#endif