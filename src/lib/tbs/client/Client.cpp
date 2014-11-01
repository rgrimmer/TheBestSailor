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
#include "client/DisplayInfo.h"

float x = 1.0f;
sf::Vector2f posView(0.0f, 0.0f);
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

    WindMap windMap(MapHeader(150, 150, 0));

    Ship ship;

    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "The Best Sailor");
    window.setKeyRepeatEnabled(true);
    sf::View currentView = window.getView();


    sf::Font font;
    if (!font.loadFromFile("/usr/share/fonts/truetype/ubuntu-font-family/UbuntuMono-R.ttf")) {
        exit(-1);
    }

    bool enableWind = false;
    bool enableFolowCamera = false;

    sf::Clock clockGlobal;
    sf::Clock clockTick;

    DisplayInfo displayInfo(&window, &font);

//    ship.advance(2.0f);
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                window.close();
                socket.disconnect();
            }
            if (event.type == sf::Event::KeyPressed) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                    posView.x -= 500.0f;
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                    posView.x += 500.0f;
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                    posView.y -= 500.0f;
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                    posView.y += 500.0f;
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                    zoomValue += 1.0f;
                    displayInfo.zoom(zoomValue);
                    currentView = sf::View(sf::FloatRect(posView.x, posView.y, SCREEN_WIDTH * zoomValue, SCREEN_HEIGHT * zoomValue));
                } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
                    zoomValue -= 1.0f;
                    displayInfo.zoom(zoomValue);
                    currentView = sf::View(sf::FloatRect(posView.x, posView.y, SCREEN_WIDTH * zoomValue, SCREEN_HEIGHT * zoomValue));
                } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::K)) {
                    ship.helm().turn(0.5f);
                } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::M)) {
                    ship.helm().turn(-0.5f);
                } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::O)) {
                    ship.advance(1.0f);
                } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::L)) {
                    ship.advance(-1.0f);
                } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                    squared = !squared;
                    mapView.load(*map, squared);
                } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
                    enableWind = !enableWind;
                } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) {
                    enableFolowCamera = !enableFolowCamera;
                }

            }
        }
        window.clear();


        sf::Time time = clockTick.getElapsedTime();
        clockTick.restart();

        // Update wind stenght on the ship
        Force windForce = windMap.force(ship.getPosition());
        
        
        // Update ship
        ship.update(time.asSeconds());

        if (enableFolowCamera) {
            currentView.setCenter(ship.getPosition());
        } else {
            currentView.setCenter(posView);
        }

        window.setView(currentView);


        // Draw map
        window.draw(mapView);

        if (enableWind)
            window.draw(windMap);


        window.draw(ship);

        // Draw information
        displayInfo.setTopLeftPosition(posView - sf::Vector2f(SCREEN_WIDTH / 2 * zoomValue, SCREEN_HEIGHT / 2 * zoomValue));

        displayInfo.draw(std::to_string(clockGlobal.getElapsedTime().asSeconds()));
        displayInfo.draw("ship :");
        displayInfo.draw("speed : " + std::to_string(ship.kinematics().speed().x) + " " + std::to_string(ship.kinematics().speed().y));
        displayInfo.draw("pos : " + std::to_string(ship.getPosition().x) + " " + std::to_string(ship.getPosition().y));
        displayInfo.draw("wind : " + windForce.toString());

        window.display();
    }


}
