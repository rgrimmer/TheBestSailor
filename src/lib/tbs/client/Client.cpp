/* 
 * File:   Client.cpp
 * Author: maxence
 * 
 * Created on 9 octobre 2014, 18:23
 */

#include "client/Client.h"
#include "client/ClientPlayer.h"

#include <thread>
#include <iostream>
#include <string>
#include <SFML/Graphics/RenderTarget.hpp>

#include <SFML/Window/Event.hpp>
#include <cmath>

#include "client/DisplayInfo.h"

#include "shared/network/Request.h"
#include "shared/network/RequestTurnHelm.h"
#include "shared/network/RequestTurnSail.h"
#include "shared/Utils.h"
#include "shared/Kinematics.h"
#include "shared/network/RequestDisconnect.h"


sf::View currentView;
sf::Vector2f posView(2000.0f, 2000.0f);
float zoomValue = 1.0f;
bool squared = true;

Client::Client() : m_player(-1, "") {
    //            startPollEventThread();
    m_enablePause = false;
    m_timeSpeed = 1.0f;
}

Client::~Client() {
    delete m_detailsView;
    delete m_globalView;
    //delete m_map;
    //delete m_wind;
}

void Client::receive(ClientUDPManager& udpManager, SynchronizedQueue<sf::Packet>& inQueue) {
    std::cout << "receive thread started" << std::endl;
    while (true) { //TODO
        sf::Packet packet = udpManager.receive();
        if (packet.getDataSize() > 0) {
            inQueue.push(packet);
        }
    }
    std::cout << "receive thread ended" << std::endl;
}

void Client::start(const std::string & name) {

    m_player.setName(name);
    
    m_world.initialize();
    //m_ship.kinematics().position() = posView;
    //m_ship.sail().setAngle(80.0f);

    //init TCP MANAGER
    if (!m_tcpManager.connect()) {
        std::cout << "Error connect" << std::endl;
        return;
    }

    //send player name
    sf::Packet packet;
    packet << static_cast<sf::Uint8> (REQ_NEW_PLAYER) << name;
    std::cout << "sending player name : " << name << "............." << std::endl;

    if (!m_tcpManager.send(packet)) {
        std::cout << "Error send" << std::endl;
        return;
    }

    //receive the map
    packet = m_tcpManager.receive();

    int width = 200, height = 200;
    double seed = 42;
   
//    packet >> width >> height >> seed;
    std::cout << width << " " << height << " " << seed << std::endl;

    // Data
    m_world.initializeMap(height, width, seed);
    
    //m_map = new HeigthMap(MapHeader(height, width, seed));
    //m_wind = new WindMap(MapHeader(height, width, seed));

    m_globalView = new GlobalView(m_world.getMap(), m_world.getWind(), m_world.getShip());
    m_detailsView = new DetailsView(m_world.getMap(), m_world.getWind(), m_world.getShip());
    m_mainGraphic = (m_mainGraphic == dynamic_cast<sf::Drawable*>(m_globalView))? dynamic_cast<sf::Drawable*>(m_detailsView) : dynamic_cast<sf::Drawable*>(m_globalView);

    m_enableFolowCamera = false;

    // receive players list
    sf::Packet playersPacket;
    std::cout << "receiving players list.........." << std::endl;
    playersPacket = m_tcpManager.receive();

    sf::Uint8 nbPlayers;
    playersPacket >> nbPlayers;

    int nbPlayersInt = static_cast<int> (nbPlayers);

    std::cout << "players list (nbPlayer=" << nbPlayersInt << ")" << std::endl;
    for (int i = 0; i < nbPlayersInt; ++i) {
        sf::Uint8 id;
        std::string playerName;

        playersPacket >> id;
        playersPacket >> playerName;

        unsigned int idUInt = static_cast<unsigned int> (id);

        if (playerName != name) {
            m_otherPlayers.push_back(ClientPlayer(idUInt, playerName));
        } else {
            m_player.setId(idUInt);
        }
    }

    m_udpManager.initialize("localhost", SERVER_PORT_UDP);

    std::thread receiver(&receive, std::ref(m_udpManager), std::ref(m_inQueue));

    //sending ident packet
    sf::Packet identPacket;
    identPacket << static_cast<sf::Uint8> (m_player.getId());
    std::cout << "sending ident packet id = " << m_player.getId() << std::endl;
    m_udpManager.send(identPacket);

    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "The Best Sailor");

    window.setKeyRepeatEnabled(true);
    currentView = window.getView();
    gameLoop(&window);

}

void Client::gameLoop(sf::RenderWindow *window) {
    // Clocks
    sf::Clock clockGlobal;
    sf::Clock clockGameLoop;
    sf::Clock clockFPS;
    int countFrames = 0;
    int fps = 0;

    // Display info

    while (window->isOpen()) {

        window->clear();

        sf::Event event;
        //    std::cout << "start poll" << std::endl;
        //        window.waitEvent(event);
        //        processEvent(window, event);
        while (window->pollEvent(event)) {

            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                // Send disconnection message
                m_udpManager.send(Request(m_player.getId(), RequestDisconnect()).getPacket());
                window->close();
            }
            if (event.type == sf::Event::KeyPressed) {
                switch (event.key.code) {
                    case sf::Keyboard::Left:
                        posView.x -= 500.0f;
                        break;
                    case sf::Keyboard::Right:
                        posView.x += 500.0f;
                        break;
                    case sf::Keyboard::Up:
                        posView.y -= 500.0f;
                        break;
                    case sf::Keyboard::Down:
                        posView.y += 500.0f;
                        break;
                    case sf::Keyboard::Subtract:
                        zoomValue *= 2.0f;
                        currentView = sf::View(sf::FloatRect(posView.x, posView.y, SCREEN_WIDTH * zoomValue, SCREEN_HEIGHT * zoomValue));
                        break;
                    case sf::Keyboard::Add:
                        zoomValue /= 2.0f;
                        currentView = sf::View(sf::FloatRect(posView.x, posView.y, SCREEN_WIDTH * zoomValue, SCREEN_HEIGHT * zoomValue));
                        break;
                    case sf::Keyboard::D:
                    {
                        m_udpManager.send(Request(m_player.getId(), RequestTurnHelm(reqOrientation::POSITIVE)).getPacket());
                        m_world.getShip().helm().turn(0.5f);
                    }
                        break;
                    case sf::Keyboard::Q:
                    {
                        m_udpManager.send(Request(m_player.getId(), RequestTurnHelm(reqOrientation::NEGATIVE)).getPacket());
                        m_world.getShip().helm().turn(-0.5f);
                    }
                        break;
                    case sf::Keyboard::Z:
                    {
                        m_udpManager.send(Request(m_player.getId(), RequestTurnSail(reqOrientation::POSITIVE)).getPacket());
                        m_world.getShip().sail().setAngle(m_world.getShip().sail().getAngle() + 5.0f);
                    }
                        break;
                        
                    case sf::Keyboard::S:
                    {
                        m_udpManager.send(Request(m_player.getId(), RequestTurnSail(reqOrientation::NEGATIVE)).getPacket());
                        m_world.getShip().sail().setAngle(m_world.getShip().sail().getAngle() - 5.0f);
                    }
                        break;
                        
                    case sf::Keyboard::A:
                        m_detailsView->switchSquared();
                        break;
                    case sf::Keyboard::W:
                        m_detailsView->switchEnableWind();
                        break;
                    case sf::Keyboard::C:
                        m_enableFolowCamera = !m_enableFolowCamera;
                        break;
                    case sf::Keyboard::P:
                        m_enablePause = !m_enablePause;
                        break;
                    case sf::Keyboard::R:
                        m_timeSpeed /= 2.0f;
                        break;
                    case sf::Keyboard::T:
                        m_timeSpeed *= 2.0f;
                        break;
                    case sf::Keyboard::M:
                            m_mainGraphic = (m_mainGraphic == dynamic_cast<sf::Drawable*>(m_detailsView))? dynamic_cast<sf::Drawable*>(m_globalView) : dynamic_cast<sf::Drawable*>(m_detailsView);
                        break;
                    default:
                        break;
                }
            }
        }

        if (!m_inQueue.empty()) {
            std::cout << "receiving msg from server.........." << std::endl;
            // TODO: handle msg
            m_inQueue.pop();
        }

        // Set view position
        if (m_enableFolowCamera) {
            currentView.setCenter(m_world.getShip().kinematics().position());
        } else {
            currentView.setCenter(posView);
        }
        window->setView(currentView);


        // Update
        float timeLoop = clockGameLoop.getElapsedTime().asSeconds();
        clockGameLoop.restart();

        // Update world

        if (!m_enablePause) {             
            m_world.update(timeLoop * m_timeSpeed);
        }

        // Draw

        // Set view position
        if (m_enableFolowCamera) {
            currentView.setCenter(m_world.getShip().kinematics().position());
        } else {
            currentView.setCenter(posView);
        }
        window->setView(currentView);

        // Draw view
        window->draw(*m_mainGraphic);

        // Draw vent apparent
        /*VectorView<float> ventAppView(apparentWind, "Va", sf::Color::Green);
        sf::Transform tApp;
        tApp.translate(m_ship.kinematics().position());
        window->draw(ventAppView, tApp);
        */

        // Display information : 
//        DisplayInfo::setZoom(zoomValue);
//        DisplayInfo::setTopLeftPosition(posView - sf::Vector2f(SCREEN_WIDTH / 2 * zoomValue, SCREEN_HEIGHT / 2 * zoomValue));
//
//        // Clocks infos
//        DisplayInfo::draw(std::to_string(clockGlobal.getElapsedTime().asSeconds()));
//        DisplayInfo::draw("fps : " + std::to_string(fps));
//
//        // Data infos
//        DisplayInfo::draw("ship :");
//        DisplayInfo::draw("ship :" + std::to_string(shipDir));
//        DisplayInfo::draw("acc : " + std::to_string(m_ship.kinematics().acceleration().x) + " " + std::to_string(m_ship.kinematics().acceleration().y));
//        DisplayInfo::draw("speed : " + std::to_string(m_ship.kinematics().speed().x) + " " + std::to_string(m_ship.kinematics().speed().y));
//        DisplayInfo::draw("pos : " + std::to_string(m_ship.kinematics().position().x) + " " + std::to_string(m_ship.kinematics().position().y));
//        //        DisplayInfo::draw("dir : " + std::to_string(dir.x) + " " + std::to_string(dir.y) + ". norme : " + std::to_string(Kinematics::norme(m_ship.kinematics().speed())));
//
//        //DisplayInfo::draw("wind : " + m_windView.force(m_ship.getPosition()).toString());
//
//        // Draw infos
//        DisplayInfo::draw("Wind Direction/Force: " + std::to_string(wind.direction()) + " " + std::to_string(wind.force()));
//        DisplayInfo::draw("WindVector: " + std::to_string(windVector.x) + " " + std::to_string(windVector.y));
//        DisplayInfo::draw("VentApparent : " + std::to_string(apparentWind.x) + " " + std::to_string(apparentWind.y));
//        DisplayInfo::draw("sailVector : " + std::to_string(sailVector.x) + " " + std::to_string(sailVector.y));
//        DisplayInfo::draw("helmVector : " + std::to_string(helmVector.x) + " " + std::to_string(helmVector.y));
//        DisplayInfo::draw("ForceDePousser : " + std::to_string(forceDePousser.x) + " " + std::to_string(forceDePousser.y));


        if (clockFPS.getElapsedTime().asSeconds() >= 1) {
            fps = countFrames;
            countFrames = 0;
            clockFPS.restart();
        } else {
            ++countFrames;
        }
        window->display();

    }

    m_world.release();
    m_tcpManager.disconnect();
}