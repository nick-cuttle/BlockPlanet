#include "Server.hpp"
#include <iostream>
#include <thread>
#include <string_view>

using PacketType = Config::PacketType;

Server::Server(unsigned short port) {

    if (listener.listen(port) != sf::Socket::Done) {
        throw std::runtime_error("Failed to bind to port");
    }
    std::cout << "Server listening on port " << port << std::endl;
}

void Server::start() {
    while (true) {
        auto client = new sf::TcpSocket();
        if (listener.accept(*client) == sf::Socket::Done) {
            std::cout << "Client connected" << std::endl;
            clients.push_back(std::move(client));
            // Handle the client in a separate thread
            std::thread(&Server::handleClient, this, client).detach();
        }
        else {
            std::cerr << "Failed to accept client" << std::endl;
        }
    }
}

void Server::broadcast(sf::Packet& packet) {
    for (sf::TcpSocket* client : clients) {
        client->send(packet);
    }
}

void Server::handleClient(sf::TcpSocket* client) {
    sf::Packet packet;
    while (client->receive(packet) == sf::Socket::Done) {
        processPacket(packet);
    }
    std::cout << "Client disconnected" << std::endl;
}

std::vector<Player> Server::getPlayers() {
    return players;
}

void Server::processPacket(sf::Packet& packet) {
    sf::Uint8 type;
    packet >> type;

    PacketType packetType = static_cast<PacketType>(type);

    sf::Packet outPacket;
    switch (packetType) {
        
        case PacketType::PLAYER_JOIN: {
            
            Player player;
            packet >> player;
            sf::Uint8 cur_size = static_cast<sf::Uint8>(players.size());
            player.setIndex(cur_size);

            std::unique_lock<std::mutex> lock(playersLock);

            players.push_back(player);
            std::cout << "Player " << player.getName() << " Added Length is now: " << players.size() << std::endl;

            lock.unlock();

            sf::Uint32 size = static_cast<sf::Uint32>(players.size());
            PacketType pJoin = PacketType::PLAYER_JOIN;
            outPacket << pJoin << size;
            for (Player p : players) {
                outPacket << p;
            }
            broadcast(outPacket);
            break;
        }


        case PacketType::PLAYER_MOVED: {
            Player p;
            packet >> p;
            players[p.getIndex()].setPosition(p.getPosition());

            PacketType pType = PacketType::PLAYER_MOVED;
            outPacket << pType << players[p.getIndex()];
            broadcast(outPacket);
            break;

        }// END PLAYER_POS

    }
}
