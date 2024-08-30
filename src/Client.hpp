#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <SFML/Network.hpp>
#include "Player.hpp"

class Client {
public:

    Client() = default;
    Client(const std::string& ipAddress, unsigned short port);
    void connect();
    void sendPacket(sf::Packet& packet);
    void processPacket(sf::Packet& packet);
    sf::TcpSocket& getSocket();
    void handleServer();
    void setPlayers(std::vector<Player>& players);


    //needs to modified with packets.
    std::vector<Player> players;

private:

    void updatePlayers(sf::Packet& packet);
    sf::TcpSocket socket;
    std::string ipAddress;
    unsigned short port;
};

#endif // CLIENT_HPP
