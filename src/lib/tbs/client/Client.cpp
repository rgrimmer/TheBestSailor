/* 
 * File:   Client.cpp
 * Author: maxence
 * 
 * Created on 9 octobre 2014, 18:23
 */

#include "client/Client.h"

#include <iostream>

#include <SFML/Graphics/RenderTarget.hpp>

#include <SFML/Window/Event.hpp>
#include <complex>

#include "shared/Utils.h"
#include "client/map/Gradient.h"
#include "client/DisplayInfo.h"

sf::View currentView;
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
float degToRad(float x)
{
    return x / 180 * M_PI;
}

sf::Vector2f operator*(const sf::Vector2f &v1, const sf::Vector2f &v2) {
    return sf::Vector2f(v1.x * v2.x, v1.y * v2.y);
}

Client::Client() {
    //            startPollEventThread();
}

Client::~Client() {
    m_socket.disconnect();
}

void Client::start(void) {

    sf::Socket::Status status = m_socket.connect("localhost", SERVER_PORT);
    if (status != sf::Socket::Done) {
        std::cout << "Error connect" << std::endl;
    }

    sf::Packet packet;
    m_socket.send(packet);
    m_socket.receive(packet);

    int width;
    int height;
    int seed;

    packet >> width >> height >> seed;
    std::cout << width << " " << height << " " << seed << std::endl;

    Gradient::initialize();

    // Data
    m_map = new HeigthMap(MapHeader(height, width, seed));
    m_wind = new WindMap(MapHeader(height, width, seed));

    //m_windView = WindMap(MapHeader(height, width, 0));
    m_windView.load(*m_wind);
    m_mapView.load(*m_map, true);

    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "The Best Sailor");


    window.setKeyRepeatEnabled(true);
    currentView = window.getView();

    m_enableWind = true;
    m_enableFolowCamera = false;


    //    startAsyncGameLoop(window);

    //    sf::Thread gameLoopThread(std::bind(&Client::gameLoop, this, &window));
    //    gameLoopThread.launch();

    gameLoop(&window);
    //    while (window.isOpen()) {
    //        pollEvent(window);
    //        
    //    }

}

void Client::gameLoop(sf::RenderWindow *window) {
    // Clocks
    sf::Clock clockGlobal;
    sf::Clock clockGameLoop;
    sf::Clock clockFPS;
    sf::Clock clockDraw;
    sf::Time timeDrawHeightMap, timeDrawWindMap;
    int countFram = 0;
    int fps = 0;

    // Display info
    sf::Font font;
    if (!font.loadFromFile("/usr/share/fonts/truetype/ubuntu-font-family/UbuntuMono-R.ttf"))
        exit(-1);

    DisplayInfo displayInfo(window, &font);

    while (window->isOpen()) {
        window->clear();

        sf::Event event;
        //    std::cout << "start poll" << std::endl;
        //        window.waitEvent(event);
        //        processEvent(window, event);
        while (window->pollEvent(event)) {

            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                window->close();
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
                    currentView = sf::View(sf::FloatRect(posView.x, posView.y, SCREEN_WIDTH * zoomValue, SCREEN_HEIGHT * zoomValue));
                } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
                    zoomValue -= 1.0f;
                    currentView = sf::View(sf::FloatRect(posView.x, posView.y, SCREEN_WIDTH * zoomValue, SCREEN_HEIGHT * zoomValue));
                } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::K)) {
                    m_ship.helm().turn(0.5f);
                } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::M)) {
                    m_ship.helm().turn(-0.5f);
                } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::O)) {
                    m_ship.advance(1.0f);
                } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::L)) {
                    m_ship.advance(-1.0f);
                } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                    squared = !squared;
                    m_mapView.load(*m_map, squared);
                } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
                    m_enableWind = !m_enableWind;
                } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) {
                    m_enableFolowCamera = !m_enableFolowCamera;
                }

            }
        }

        // Set view position
        if (m_enableFolowCamera) {
            currentView.setCenter(m_ship.getPosition());
        } else {
            currentView.setCenter(posView);
        }
        window->setView(currentView);


        // Update
        float timeLoop = clockGameLoop.getElapsedTime().asSeconds();
        clockGameLoop.restart();

        sf::Vector2f CONSTANTE(1, 1);
        // Update ship
        m_ship.update(timeLoop);
        sf::Vector2f moveForce = -m_ship.kinematics().speed();
        sf::Vector2f windForce = m_wind->wind(static_cast<sf::Vector2i>(m_ship.getPosition())).getVector();
        
        sf::Vector2f ventApparent = windForce + moveForce; 
        float angleSailWind = m_ship.sail().getAngleWith(ventApparent);
        sf::Vector2f forceDePousser = CONSTANTE * ventApparent * ventApparent * sf::Vector2f(std::sin(degToRad(angleSailWind)), std::sin(degToRad(angleSailWind)));
        m_ship.kinematics().acceleration() = forceDePousser * sf::Vector2f(0.00001, 0.00001);

        // Draw


        // Draw heightMap
        clockDraw.restart();
        window->draw(m_mapView);
        timeDrawHeightMap = clockDraw.getElapsedTime();

        // Draw windMap
        if (m_enableWind) {
            clockDraw.restart();
            window->draw(m_windView);
            timeDrawWindMap = clockDraw.getElapsedTime();
        }

        // Draw ship
        window->draw(m_ship);



        // Display information : 
        displayInfo.zoom(zoomValue);
        displayInfo.setTopLeftPosition(posView - sf::Vector2f(SCREEN_WIDTH / 2 * zoomValue, SCREEN_HEIGHT / 2 * zoomValue));

        // Clocks infos
        displayInfo.draw(std::to_string(clockGlobal.getElapsedTime().asSeconds()));
        displayInfo.draw("fps : " + std::to_string(fps));

        // Data infos
        displayInfo.draw("ship :");
        displayInfo.draw("speed : " + std::to_string(m_ship.kinematics().speed().x) + " " + std::to_string(m_ship.kinematics().speed().y));
        displayInfo.draw("pos : " + std::to_string(m_ship.getPosition().x) + " " + std::to_string(m_ship.getPosition().y));
        //displayInfo.draw("wind : " + m_windView.force(m_ship.getPosition()).toString());

        // Draw infos
        displayInfo.draw("Draw(ms)");
        displayInfo.draw("HeightMap : " + std::to_string(timeDrawHeightMap.asMilliseconds()));
        displayInfo.draw("WindMap : " + std::to_string(timeDrawWindMap.asMilliseconds()));
        displayInfo.draw("Force : " + std::to_string(forceDePousser.x) + " " + std::to_string(forceDePousser.y));


        if (clockFPS.getElapsedTime().asSeconds() >= 1) {
            fps = countFram;
            countFram = 0;
            clockFPS.restart();
        } else {
            ++countFram;
        }
        window->display();

    }

    m_socket.disconnect();
}