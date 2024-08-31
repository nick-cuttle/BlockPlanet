#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include "Client.hpp"
#include "Config.hpp"
#include <iostream>
#include "MenuScreen.h"

int main()
{   
    using PacketType = Config::PacketType;
    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();

    //sf::Style::Fullscreen
    sf::RenderWindow window(desktopMode, "BlockPlanet", sf::Style::Fullscreen);
    //const sf::Vector2u wSize(400, 400);
    //window.setSize(wSize);
    /*window.setVerticalSyncEnabled(false);

    sf::Vector2f playerPos = sf::Vector2f(desktopMode.width / 2, desktopMode.height / 2);

    std::string name;

    std::cout << "Enter your name: ";
    std::getline(std::cin, name);


    std::vector<Player> players{};

    Player player{name, playerPos};

    Client client{ Config::SERVER_IP, Config::SERVER_PORT };
    client.connect();;

    sf::Packet joinPacket;
    PacketType joinType = PacketType::PLAYER_JOIN;
 
    joinPacket << joinType << player;
    client.sendPacket(joinPacket);*/

    //create the Screen;
    MenuScreen menuScreen{ &window };


    while (window.isOpen())
    {   

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) window.close();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) window.close();

            menuScreen.handleButtons(event);

        }

        if (Config::gameState == Config::GameState::MENU) {
            menuScreen.draw();
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

    return 0;
}
