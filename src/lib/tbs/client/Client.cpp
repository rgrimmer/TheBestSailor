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
#include "shared/Utils.h"
#include "client/Gradient.h"

float x = 1.0f;
float posViewX = 0.0f;
float posViewY = 0.0f;
float zoomValue = 1.0f;
bool squared = true;

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
    //UdpSocketManager udpSocketManager;

    // Attribution d'un port automatique
    //udpSocketManager.bind();

    // @TODO se connecter au serveur
    //udpSocketManager.connectTo(UdpSocketManager::serverAddress, UdpSocketManager::serverPort);

    Gradient::initialize();

    Map *map;
    MapHeader mapHeader;

    // @TODO attendre une map
    //receiveMap(mapHeader, udpSocketManager);

    //map = new Map(mapHeader);
    map = new Map(MapHeader(NB_TILES_WIDTH, NB_TILES_HEIGHT, rand()));

    std::cout << map->getWidth() << " " << map->getHeight() << " " << map->getSeed() << std::endl;
    TileMap mapView;
    mapView.load(*map, true);


    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "The Best Sailor");
    window.setKeyRepeatEnabled(true);
    sf::View currentView = window.getView();
    
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                window.close();

            if (event.type == sf::Event::KeyPressed) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                    posViewX -= 500.0f;
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                    posViewX += 500.0f;
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                    posViewY -= 500.0f;
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                    posViewY += 500.0f;
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                    zoomValue += 1.0f;
                    currentView = sf::View(sf::FloatRect(posViewX, posViewY, SCREEN_WIDTH * zoomValue, SCREEN_HEIGHT * zoomValue));
                } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
                    zoomValue -= 1.0f;
                    currentView = sf::View(sf::FloatRect(posViewX, posViewY, SCREEN_WIDTH * zoomValue, SCREEN_HEIGHT * zoomValue));
                } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                    squared = !squared;
                    mapView.load(*map, squared);
                }

            }
        }

        window.clear();
        currentView.setCenter(posViewX, posViewY);
        window.setView(currentView);
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