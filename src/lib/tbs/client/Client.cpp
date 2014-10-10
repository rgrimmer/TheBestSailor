/* 
 * File:   Client.cpp
 * Author: maxence
 * 
 * Created on 9 octobre 2014, 18:23
 */

#include "client/Client.h"

#include <iostream>

#include <SFML/Network/Packet.hpp>
#include <SFML/Network/UdpSocket.hpp>
#include <SFML/Network/IpAddress.hpp>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include <SFML/Window/Event.hpp>

#include "shared/Map.h"
#include "client/TileMap.h"

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
    Map map;
    mapPacket >> map;²
    //map.generate(800,600); // @TODO remove it

    // @TODO l'afficher
    TileMap mapView;
    mapView.load(sf::Vector2u(100,100), map);
    sf::RenderWindow window(sf::VideoMode(800, 600), "The Best Sailor");
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        //window.setView(window.getView().setCenter(400,200));
        window.draw(mapView);
        window.display();
    }
}