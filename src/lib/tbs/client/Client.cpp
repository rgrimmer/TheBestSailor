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

#include "client/TileMap.h"

sf::Packet& operator>>(sf::Packet &packet, Map &map) {

    //assert(packet.getDataSize() >= map.size() * sizeof (float) + sizeof(sf::Int32) * 2);

    int mapWidth;
    int mapHeight;

    // @TODO add cast(sf::int32)
    packet >> mapWidth >> mapHeight;
    map.allocate(mapWidth, mapHeight);

    std::cout << "packet to map : " << mapWidth << " " << mapHeight << std::endl;
    // @TODO add cast (float)
    for (int i = 0; i < mapWidth; ++i) {
        for (int j = 0; j < mapHeight; ++j) {
            packet >> map(i,j);
        }

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
    Map map;
    UdpSocketManager udpSocketManager;

    // Attribution d'un port automatique
    udpSocketManager.bind();

    // @TODO se connecter au serveur
    udpSocketManager.connectTo(UdpSocketManager::serverAddress, UdpSocketManager::serverPort);


    // @TODO attendre une map
    receiveMap(map, udpSocketManager);




    TileMap mapView;
    //mapView.load(sf::Vector2u(1,1), map);

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

void Client::receiveMap(Map &map, UdpSocketManager &connectionManager) {
    sf::Packet mapPacket; // Temp
    sf::IpAddress serverIp; // Unused
    unsigned short serverPort; // Unused
    connectionManager.receive(mapPacket, serverIp, serverPort);
    mapPacket >> map;
    //    std::cout << "Received " << mapPacket.getDataSize() << " bytes from " << serverIp << " on port " << serverPort << std::endl;
}