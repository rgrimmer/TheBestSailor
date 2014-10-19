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
#include "shared/MapHeader.h"

sf::Packet& operator>>(sf::Packet &packet, MapHeader &header) {

    //assert(packet.getDataSize() >= map.size() * sizeof (float) + sizeof(sf::Int32) * 2);

    sf::Int32 mapWidth;
    sf::Int32 mapHeight;
    sf::Int32 mapSeed;

    // @TODO add cast(sf::int32)
    packet >> mapWidth >> mapHeight >> mapSeed;
    
    header = MapHeader(mapWidth, mapHeight, mapSeed);

    std::cout << "packet to map : " << mapWidth << " " << mapHeight << " " << mapSeed << std::endl;

    return packet;
}

Client::Client() {

}

Client::Client(const Client& orig) {
}

Client::~Client() {
}

void Client::start(void) {
    UdpSocketManager udpSocketManager;

    // Attribution d'un port automatique
    udpSocketManager.bind();

    // @TODO se connecter au serveur
    udpSocketManager.connectTo(UdpSocketManager::serverAddress, UdpSocketManager::serverPort);

    Map *map;
    MapHeader mapHeader;
    
    // @TODO attendre une map
    receiveMap(mapHeader, udpSocketManager);

    map = new Map(mapHeader);


    TileMap mapView;
    mapView.load(*map, true);

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

void Client::receiveMap(MapHeader &header, UdpSocketManager &connectionManager) {
    sf::Packet mapPacket; // Temp
    sf::IpAddress serverIp; // Unused
    unsigned short serverPort; // Unused
    connectionManager.receive(mapPacket, serverIp, serverPort);
    mapPacket >> header;
    //    std::cout << "Received " << mapPacket.getDataSize() << " bytes from " << serverIp << " on port " << serverPort << std::endl;
}