#ifndef SERVER_HPP
#define SERVER_HPP

#include <SFML/Network.hpp>
#include <vector>
#include <memory>
#include "../../src/Player.hpp"
#include <mutex>
#include "../../src/Config.hpp"

class Server {
public:

    void start();
    std::vector<Player> getPlayers();
    Server(unsigned short port);


private:

    void handleClient(sf::TcpSocket* client);
    void processPacket(sf::Packet& packet);
    void broadcast(sf::Packet& packet);

    sf::TcpListener listener;
    std::vector<sf::TcpSocket *> clients;

    std::vector<Player> players{};
    std::mutex playersLock;


};

#endif // SERVER_HPP
