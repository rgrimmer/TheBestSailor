/* 
 * File:   Client.cpp
 * Author: maxence
 * 
 * Created on 9 octobre 2014, 18:23
 */

#include "client/Client.h"

#include <iostream>
#include <SFML/Network.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include "shared/TileMap.h"

Client::Client() {

}

Client::Client(const Client& orig) {
}

Client::~Client() {
}

void Client::start(void) {
    sf::UdpSocket socket;
    sf::IpAddress ipServer = "localhost";
    unsigned short portServer = 54000;

    sf::Packet p;
    // @warning seulement p ou p = sf::Packet()
    // @TODO se connecter au serveur
    if (socket.send(p, ipServer, portServer) != sf::Socket::Done) {
        // erreur...
        std::cerr << "Err send" << std::endl;
    }

    sf::Packet mapPacket;
    // @TODO attendre une map
    if (socket.receive(mapPacket, ipServer, portServer) != sf::Socket::Done) {
        //std::cerr << "Err receive" << std::endl;
        // erreur...
    }
    std::cout << "Received " << mapPacket.getDataSize() << " bytes from " << ipServer << " on port " << portServer << std::endl;
    TileMap map = TileMap();
    map << mapPacket;

    // @TODO l'afficher
    sf::RenderWindow window(sf::VideoMode(800, 600), "The Best Sailor");
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        //window.setView(window.getView().setCenter(400,200));
        window.draw(map);
        window.display();
    }
}