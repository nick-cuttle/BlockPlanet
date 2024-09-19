#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <SFML/Network.hpp>
#include "Player.hpp"
#include "MenuScreen.h"
#include "GameScreen.hpp"
#include "TexureManager.hpp"

class Client {
public:

    Client();
    //Client(const std::string& ipAddress, unsigned short port);
    void connect();
    void sendPacket(sf::Packet& packet);
    void processPacket(sf::Packet& packet);
    sf::TcpSocket& getSocket();
    void handleServer();
    void setPlayers(std::vector<Player>& players);
    void run();
    
    //screens
    MenuScreen menuScreen;
    GameScreen gameScreen;


    TextureManager textureManager;

    //needs to modified with packets.
    std::vector<Player> players;
    Player player;

    sf::RenderWindow window;

private:

    void updatePlayers(sf::Packet& packet);
    void initGameState();


    sf::TcpSocket socket;
    std::string ipAddress;
    unsigned short port;
};

#endif // CLIENT_HPP
