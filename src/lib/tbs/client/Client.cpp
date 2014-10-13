/* 
 * File:   Client.cpp
 * Author: maxence
 * 
 * Created on 9 octobre 2014, 18:23
 */

#include "client/Client.h"

#include <iostream>

//#include <SFML/Network/Packet.hpp>
#include <SFML/Network/UdpSocket.hpp>
#include <SFML/Network/IpAddress.hpp>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include <SFML/Window/Event.hpp>

#include "shared/Map.h"
#include "client/TileMap.h"
#include "shared/ConnectionManager.h"

sf::Packet& operator>> (sf::Packet &packet, Map &map) {

    //assert(packet.getDataSize() >= map.size() * sizeof (float) + sizeof(sf::Int32) * 2);

    packet >> map.rwidth() >> map.rheight(); 
    map.create();
    
    int mapSize = map.size();
    std::cout << "packet to map : "<< mapSize << " " << map.width() << " " << map.height() << std::endl;
    // @TODO add cast (float)
    for (int i = 0; i < mapSize; ++i) {
        packet >> map[i];
    }

    return packet;
}

Client::Client() {

}

Client::Client(const Client& orig) {
}

Client::~Client() {
}

void Client::start(void) {
    std::cout << "client start " << ConnectionManager::clientPort << std::endl;

    ConnectionManager connectionManager;
    connectionManager.bind(ConnectionManager::clientPort);

    // @TODO se connecter au serveur
    //socket.bind(clientPort);
    //if (socket.send(p, ipServer, portServer) != sf::Socket::Done) {
    //    // erreur...
    //    std::cerr << "Err send" << std::endl;
    //}
    std::cout << "test" << std::endl;
    sf::IpAddress ipServer;
    unsigned short portServer;
    sf::Packet mapPacket;
    
    // @TODO attendre une map
    connectionManager.receive(mapPacket, ipServer, portServer);
    /*
    if (socket.receive(mapPacket, ipServer, portServer) != sf::Socket::Done) {
        std::cerr << "Err receive" << std::endl;
        // erreur...
    }*/
    std::cout << "Received " << mapPacket.getDataSize() << " bytes from " << ipServer << " on port " << portServer << std::endl;
    Map map;
    //truc(mapPacket, map);
    mapPacket >> map;
    //operator>>(mapPacket, map);
    //map.generate(800,600); // @TODO remove it

    
    TileMap mapView;
    mapView.load(sf::Vector2u(1,1), map);
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