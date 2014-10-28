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

#include "client/map/TileMap.h"
#include "shared/map/MapHeader.h"
#include "shared/Utils.h"
#include "client/map/Gradient.h"
#include "shared/Player.h"

float x = 1.0f;
float posViewX = 0.0f;
float posViewY = 0.0f;
float zoomValue = 1.0f;
bool squared = true;

sf::Packet& operator>>(sf::Packet &packet, MapHeader &header) {
    std::cout << packet.getDataSize() << std::endl;

    //assert(packet.getDataSize() >= map.size() * sizeof (float) + sizeof(sf::Int32) * 2);

    sf::Int32 mapWidth;
    sf::Int32 mapHeight;
    sf::Int32 mapSeed;

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


    sendConnectionToServer();
    receiveCommSocket();
    HeigthMap *map = receiveMap();

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

void Client::sendConnectionToServer(void) {
    m_socketReader.setRemoteAdress(UdpSocketManager::serverAddress);
    m_socketReader.setRemotePort(UdpSocketManager::serverPort);
    m_socketReader.send((sf::Packet() << m_player.getName()));
}

void Client::receiveCommSocket(void) {
    sf::Packet packetReceive;
    sf::IpAddress remoteAddress;
    unsigned short remotePort;
        std::cout << "wait comm socket of server" << std::endl;
    m_socketReader.getSocket()->receive(packetReceive, remoteAddress, remotePort);
    m_socketReader.setRemoteAdress(remoteAddress);
    m_socketReader.setRemotePort(remotePort);
    std::cout << "serv : "<< packetReceive << " " << remoteAddress << " " << remotePort << std::endl;
}

HeigthMap* Client::receiveMap(void) {
    
    m_socketReader.read();
    
    MapHeader mapHeader;
    sf::Packet packetHeader = m_socketReader.getBuffer()->pop();
    packetHeader >> mapHeader;
    
    return new HeigthMap(mapHeader);
    //    std::cout << "Received " << mapPacket.getDataSize() << " bytes from " << serverIp << " on port " << serverPort << std::endl;
}