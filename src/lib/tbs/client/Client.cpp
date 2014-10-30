/* 
 * File:   Client.cpp
 * Author: maxence
 * 
 * Created on 9 octobre 2014, 18:23
 */

#include "client/Client.h"

#include <iostream>

//#include <SFML/Network/Packet.hpp>
#include <SFML//Network.hpp>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include <SFML/Window/Event.hpp>

#include "client/map/TileMap.h"
#include "shared/map/MapHeader.h"
#include "shared/Utils.h"
#include "client/map/Gradient.h"
#include "shared/map/WindMap.h"
#include "shared/ship/Ship.h"

float x = 1.0f;
float posViewX = 0.0f;
float posViewY = 0.0f;
float zoomValue = 1.0f;
bool squared = true;

/*sf::Packet& operator>>(sf::Packet &packet, MapHeader &header) {
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
 */

Client::Client() {

}

Client::Client(const Client& orig) {
}

Client::~Client() {
}

void Client::start(void) {

    sf::TcpSocket socket;
    sf::Socket::Status status = socket.connect("localhost", SERVER_PORT);
    if (status != sf::Socket::Done) {
        std::cout << "Error connect" << std::endl;
    }

    sf::Packet packet;
    socket.send(packet);
    socket.receive(packet);

    int width;
    int height;
    int seed;

    packet >> width >> height >> seed;
    std::cout << width << " " << height << " " << seed << std::endl;
    
    Gradient::initialize();

    HeigthMap *map = new HeigthMap(MapHeader(height, width, seed));

    TileMap mapView;
    mapView.load(*map, true);

    WindMap windMap(MapHeader(150,150,0));
    
    Ship ship;

    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "The Best Sailor");
    window.setKeyRepeatEnabled(true);
    sf::View currentView = window.getView();

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                window.close();
                socket.disconnect();
            }
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
                } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::J)) {
                    ship.turnLeft(0.5f);
                } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::L)) {
                    ship.turnRight(0.5f);
                } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                    squared = !squared;
                    mapView.load(*map, squared);
                }

            }
        }
        ship.advance(2);
        window.clear();
        currentView.setCenter(posViewX, posViewY);
        window.setView(currentView);
        window.draw(mapView);
	window.draw(windMap);
	window.draw(ship);
        window.display();
    }


}
