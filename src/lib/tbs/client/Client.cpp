/* 
 * File:   Client.cpp
 * Author: maxence
 * 
 * Created on 9 octobre 2014, 18:23
 */

#include "client/Client.h"
#include "client/ClientPlayer.h"

#include <iostream>
#include <string>
#include <SFML/Graphics/RenderTarget.hpp>

#include <SFML/Window/Event.hpp>
#include <cmath>

#include "client/DisplayInfo.h"

#include "shared/network/UtilsNetwork.h"
#include "shared/network/Request.h"
#include "shared/network/RequestTurnHelm.h"
#include "shared/network/RequestTurnSail.h"
#include "shared/network/RequestDisconnect.h"
#include "shared/Utils.h"
#include "shared/Kinematics.h"
#include "shared/map/Map.h"


sf::View currentView;
sf::Vector2f posView(2000.0f, 2000.0f);
float zoomValue = 1.0f;
bool squared = true;

Client::Client()
: m_window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "The Best Sailor")
, m_enableFolowCamera(true)
, m_enablePause(false)
, m_timeSpeed(1.0f)
, m_player(-1, "Unamed")
, m_udpReceiveThread(nullptr)
, m_mainGraphic(nullptr)
, m_detailsView(nullptr)
, m_globalView(nullptr) {
    //            startPollEventThread();
}

Client::~Client() {
    delete m_detailsView;
    delete m_globalView;
    delete m_udpReceiveThread;
    //delete m_map;
    //delete m_wind;
}

void Client::receive() {
    std::cout << "[Client][Start] \tUDP Receive thread started" << std::endl;
    while (true) { //TODO
        sf::Packet packet = m_udpManager.receive();
        if (packet.getDataSize() > 0) {
            m_inQueue.push(packet);
        }
    }
    std::cout << "[Client][Stop] \tUDP Receive thread ended" << std::endl;
}

void Client::start(const std::string & name) {

    m_player.setName(name);

    m_world.initialize();
    //m_ship.kinematics().position() = posView;
    //m_ship.sail().setAngle(80.0f);
    
    // Connect, Send name, Receive ID
    initConnectionWithServer();
    
    bool continued = false;
    do {
        
    // Wait receive map and send ack ready
    initGame();
    // Start gameloop
    continued = startGame();
    
    } while(continued);
    
}

void Client::initConnectionWithServer() {
    //init TCP MANAGER
    if (!m_tcpManager.connect()) {
        std::cout << "Error connect" << std::endl;
        return;
    }

    //send player name
    sf::Packet packet;
    packet << static_cast<sf::Uint8> (REQ_NEW_PLAYER) << m_player.getName();
    std::cout << "sending player name : " << m_player.getName() << "............." << std::endl;

    if (!m_tcpManager.send(packet)) {
        std::cout << "Error send" << std::endl;
        return;
    }
}

void Client::initGame() {

    sf::Packet packetMap;
    //receive the map
    packetMap = m_tcpManager.receive();

    int width = 200, height = 200;
    double seed = 42;

        packetMap >> width >> height >> seed;
    std::cout << width << " " << height << " " << seed << std::endl;

    // Data
    Map *t_map = new Map(MapHeader(width, height, seed));
//    packet >> (*t_map);
    m_world.setMap(t_map);
    //    m_world.initializeMap(height, width, seed);

    //m_map = new HeigthMap(MapHeader(height, width, seed));
    //m_wind = new WindMap(MapHeader(height, width, seed));

    m_globalView = new GlobalView(m_world.getMap(), m_world.getWind(), m_world.getShip());
    m_detailsView = new DetailsView(m_world.getMap(), m_world.getWind(), m_world.getShip());
    m_mainGraphic = dynamic_cast<sf::Drawable*> (m_globalView);

    m_enableFolowCamera = true;

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

        if (playerName != m_player.getName()) {
            m_otherPlayers.push_back(ClientPlayer(idUInt, playerName));
        } else {
            m_player.setId(idUInt);
        }
    }

    m_udpManager.initialize("localhost", SERVER_PORT_UDP);

    m_udpReceiveThread = new std::thread(&Client::receive, this);

    //sending ident packet
    sf::Packet identPacket;
    identPacket << static_cast<sf::Uint8> (m_player.getId());
    std::cout << "sending ident packet id = " << m_player.getId() << std::endl;
    m_udpManager.send(identPacket);

    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "The Best Sailor");

    window.setKeyRepeatEnabled(true);
    currentView = window.getView();
}

bool Client::startGame() {
    // Clocks
    sf::Clock clockGlobal;
    sf::Clock clockGameLoop;
    sf::Clock clockFPS;
    int countFrames = 0;
    int fps = 0;

    // Display info

    while (m_window.isOpen()) {

        m_window.clear();

        sf::Event event;
        //    std::cout << "start poll" << std::endl;
        //        window.waitEvent(event);
        //        processEvent(window, event);
        while (m_window.pollEvent(event)) {

            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                // Send disconnection message
                m_udpManager.send(Request(m_player.getId(), RequestDisconnect()).getPacket());
                m_window.close();
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
                        m_mainGraphic = (m_mainGraphic == dynamic_cast<sf::Drawable*> (m_detailsView)) ? dynamic_cast<sf::Drawable*> (m_globalView) : dynamic_cast<sf::Drawable*> (m_detailsView);
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
        m_window.setView(currentView);


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
        m_window.setView(currentView);

        // Draw view
        m_window.draw(*m_mainGraphic);

        // Draw vent apparent
        /*VectorView<float> ventAppView(apparentWind, "Va", sf::Color::Green);
        sf::Transform tApp;
        tApp.translate(m_ship.kinematics().position());
        m_window.draw(ventAppView, tApp);
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
        m_window.display();

    }

    m_world.release();
    return m_window.isOpen();
}