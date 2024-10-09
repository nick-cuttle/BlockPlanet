#include "Client.hpp"
#include <thread>
#include <iostream>

using PacketType = Config::PacketType;

Client::Client()
    : 
    window(sf::VideoMode::getDesktopMode(), "BlockPlanet", sf::Style::Fullscreen),
    ipAddress(Config::SERVER_IP), 
    port(Config::SERVER_PORT),
    menuScreen(&window),
    players({}),
    player(),
    gameScreen(&window, &players, &player)
{
    window.setFramerateLimit(60);
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
        if (p == this->player) {
            this->player = p;
            std::cout << "Player Pos: " << this->player.getPosition().x << "  " << this->player.getPosition().y << std::endl;
        }
    }

    gameScreen.setPlayers(&players);
    gameScreen.setPlayer(&( this->player) );
    
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


    }//END SWITCH

}

void Client::initGameState()
{
    //update gameState:

    std::string nameText = menuScreen.getNameButton()->getText().getString().toAnsiString();
    player.setName(nameText);

    sf::Packet joinPacket;
    PacketType joinType = PacketType::PLAYER_JOIN;
 
    joinPacket << joinType << player;
    sendPacket(joinPacket);

    Config::gameState = Config::GameState::RUNNING;
}

/// @brief runner for the client, handles running the window
void Client::run()
{

    while (window.isOpen())
    {   

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) window.close();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) window.close();

            menuScreen.handleButtons(event);

        }
        
        if (Config::gameState == Config::GameState::RUNNING) {
            gameScreen.draw();
        }
        else if (Config::gameState == Config::GameState::MENU) {
            menuScreen.draw();
        }
        else if (Config::gameState == Config::GameState::INITILIZATION) {
            initGameState();
        }

        //window.clear();
        //for (Player& p : client.players) {

        //    if (p.getName() == player.getName()) {

        //        if (window.hasFocus())
        //            p.move();
        //        //if moved send packet to server.
        //        if (p.getHasMoved()) {
        //            sf::Packet packet;
        //            PacketType pt = PacketType::PLAYER_MOVED;
        //            packet << pt << p;
        //            client.sendPacket(packet);
        //        }
        //    }
        //    p.draw(window);
        //}

        //window.display();
    }
}