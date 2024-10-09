#include "GameScreen.hpp"
#include "Config.hpp"

void GameScreen::draw()
{

    if (!window->hasFocus()) {
        return;
    }
    window->clear();
    terrain.render(player->getPosition(), window);
    for (Player& p : *players) {

        //    if (p.getName() == player.getName()) {

        //        if (window->hasFocus())
        //            p.move();
               //if moved send packet to server.
            //    if (p.getHasMoved()) {
            //        sf::Packet packet;
            //        PacketType pt = PacketType::PLAYER_MOVED;
            //        packet << pt << p;
            //        client.sendPacket(packet);
            //    }
        //    }
           p.move();
           p.draw(*window);
        }
    window->display();
}

void GameScreen::handleButtons(sf::Event event)
{
}
