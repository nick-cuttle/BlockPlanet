#ifndef GAMESCREEN_HPP
#define GAMESCREEN_HPP

#include "Screen.h"
#include "Player.hpp"
#include "Terrain.hpp"

class GameScreen : public Screen {

private:

    std::vector<Player>* players;
    Terrain terrain;
    Player* player;
    


public:

    GameScreen() = default;
    GameScreen(sf::RenderWindow* win, std::vector<Player>* plys, Player* p)
        :
        Screen(win),
        players(plys),
        terrain(12345),
        player(p)
    {
    }

    void draw();
	void handleButtons(sf::Event event);

    void setPlayers(std::vector<Player>* players) {
        this->players = players;
    }

    void setPlayer(Player* p) { this->player = &(*players)[p->getIndex()];}



};






#endif