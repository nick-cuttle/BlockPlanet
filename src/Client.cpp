#include "Client.hpp"
#include "Config.hpp"
#include <thread>
#include <iostream>
using PacketType = Config::PacketType;

Client::Client(const std::string& ipAddress, unsigned short port)
    : ipAddress(ipAddress), port(port)
{
}

void Client::connect() {
    socket.connect(ipAddress, port);

    std::thread(&Client::handleServer, this).detach();
    //handle setting up thread for packets.
}

void Client::sendPacket(sf::Packet& packet) {
    socket.send(packet);
}

sf::TcpSocket& Client::getSocket() {
    return socket;
}

void Client::handleServer() {

    sf::Packet packet;
    while (socket.receive(packet) == sf::Socket::Done) {
        processPacket(packet);
    }

}

void Client::setPlayers(std::vector<Player>& players) {
    this->players = players;
}

void Client::updatePlayers(sf::Packet& packet) {

    sf::Uint32 size;
    packet >> size;
    players.clear();

    players.resize(size);  // Resize the vector to hold all players

    // Deserialize each player
    for (Player& player : players) {
        Player p;
        packet >> p;
        player = p;
    }
    
}

void Client::processPacket(sf::Packet& packet) {
    sf::Uint8 type;
    packet >> type;

    PacketType packetType = static_cast<PacketType>(type);

    switch (packetType) {

    case PacketType::PLAYER_JOIN: {

        updatePlayers(packet);
        std::cout << "CLIENT: PLAYERS LIST SIZE: " << players.size() << std::endl;
        break;
    }


    case PacketType::PLAYER_MOVED: {

        Player p;
        packet >> p;
        players[p.getIndex()].setPosition(p.getPosition());

        break;

    }// END PLAYER_POS


    }


}