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

#include "client/map/Gradient.h"
#include "client/DisplayInfo.h"

#include "shared/network/Request.h"
#include "shared/network/RequestTurnHelm.h"
#include "shared/network/RequestTurnSail.h"
#include "shared/Utils.h"
#include "shared/Kinematics.h"


sf::View currentView;
sf::Vector2f posView(2000.0f, 2000.0f);
float zoomValue = 1.0f;
bool squared = true;

sf::Vector2f operator*(const sf::Vector2f &v1, const sf::Vector2f &v2) {
    return sf::Vector2f(v1.x * v2.x, v1.y * v2.y);
}

sf::Vector2f operator*(const sf::Vector2f &v1, float coef) {
    return sf::Vector2f(v1.x * coef, v1.y * coef);
}

sf::Vector2f operator/(const sf::Vector2f &v1, const sf::Vector2f &v2) {
    return sf::Vector2f(v1.x / v2.x, v1.y / v2.y);
}

Client::Client() : m_player(-1, "") {
    //            startPollEventThread();
    m_enablePause = false;
    m_timeSpeed = 1.0f;
}

Client::~Client() {
    delete m_detailsView;
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
    m_ship.kinematics().position() = posView;

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

    int width, height;
    double seed;

    packet >> width >> height >> seed;
    std::cout << width << " " << height << " " << seed << std::endl;

    Gradient::initialize();

    // Data
    m_map = new HeigthMap(MapHeader(height, width, seed));
    m_wind = new WindMap(MapHeader(height, width, seed));

    m_detailsView = new DetailsView(*m_map, *m_wind, m_ship);

    m_enableFolowCamera = false;

    //receive players list
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
        m_enableFolowCamera = false;

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
    int countFram = 0;
    int fps = 0;

    // Display info


    DisplayInfo::setWindow(window);

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
                    case sf::Keyboard::Add:
                        zoomValue *= 2.0f;
                        currentView = sf::View(sf::FloatRect(posView.x, posView.y, SCREEN_WIDTH * zoomValue, SCREEN_HEIGHT * zoomValue));
                        break;
                    case sf::Keyboard::Subtract:
                        zoomValue /= 2.0f;
                        currentView = sf::View(sf::FloatRect(posView.x, posView.y, SCREEN_WIDTH * zoomValue, SCREEN_HEIGHT * zoomValue));
                        break;
                    case sf::Keyboard::D:
                    {
                        m_udpManager.send(RequestTurnHelm(REQ_ACTION_TURN_HELM_POSITIVE, m_player.getId()).createPacket());
                        m_ship.helm().turn(0.5f);
                    }
                        break;
                    case sf::Keyboard::Q:
                    {
                        m_udpManager.send(RequestTurnHelm(REQ_ACTION_TURN_HELM_NEGATIVE, m_player.getId()).createPacket());
                        m_ship.helm().turn(-0.5f);
                    }
                        break;
                    case sf::Keyboard::Z:
                    {
                        m_udpManager.send(RequestTurnSail(REQ_ACTION_TURN_SAIL_POSITIVE, m_player.getId()).createPacket());
                        m_ship.sail().setAngle(m_ship.sail().getAngle() + 5.0f);
                    }
                        break;
                        
                    case sf::Keyboard::S:
                    {
                        m_udpManager.send(RequestTurnSail(REQ_ACTION_TURN_SAIL_NEGATIVE, m_player.getId()).createPacket());
                        m_ship.sail().setAngle(m_ship.sail().getAngle() - 5.0f);
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
                    case sf::Keyboard::I:
                        m_timeSpeed /= 2.0f;
                        break;
                    case sf::Keyboard::O:
                        m_timeSpeed *= 2.0f;
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
            currentView.setCenter(m_ship.kinematics().position());
        } else {
            currentView.setCenter(posView);
        }
        window->setView(currentView);


        // Update
        float timeLoop = clockGameLoop.getElapsedTime().asSeconds();
        clockGameLoop.restart();

        // Update ship

        Wind wind = m_wind->wind(static_cast<sf::Vector2i> (m_ship.kinematics().position() / sf::Vector2f(TILE_SIZE, TILE_SIZE)));

        sf::Vector2f shipVector = m_ship.kinematics().speed();
        sf::Vector2f windVector = wind.getVector();

        sf::Vector2f coefSail(1.0f, 1.0f);
        sf::Vector2f coefHelm(1.0f, 1.0f);

        sf::Vector2f frottement(0.001f, 0.001f);
        sf::Vector2f apparentWind = windVector - shipVector;

        float apparentWindDir = Kinematics::direction(apparentWind);
        float sailDir = Kinematics::degToRad(m_ship.sail().getAngle());
        float helmDir = Kinematics::degToRad(m_ship.helm().angle());
        float shipDir = Kinematics::degToRad(Kinematics::direction(m_ship.kinematics().speed()));
        if (isnan(shipDir))
            shipDir = 0;

        float angleAlpha = 0.0f; // @TODO angle ventApparent - voile
        //        float angleAlpha = 
        float angleBeta = shipDir - sailDir; // @TODO angle axe du bateau - voile 

        // Equation from https://www.ensta-bretagne.fr/jaulin/jaulincifa2004.pdf

        sf::Vector2f sailVector =
                coefSail * (
                windVector * std::cos(shipDir + angleBeta)
                - shipVector * std::sin(shipDir)
                );

        sf::Vector2f helmVector = coefHelm * shipVector * std::sin(helmDir);

        sf::Vector2f forceDePousser1 =
                (sailVector * std::sin(angleBeta)
                - helmVector * std::sin(helmDir)
                - shipVector * frottement)
                / 1.0f; // Masse

        // Equation from wikipedia
        sf::Vector2f CONSTANTE(0.1f, 0.1f);
        float sinAB = std::sin(angleAlpha + angleBeta);
        sf::Vector2f forceDePousser2 = CONSTANTE * sinAB * angleAlpha - helmVector * std::sin(helmDir);

        sf::Vector2f forceDePousser = forceDePousser1;

        m_ship.kinematics().acceleration() = forceDePousser /* Kinematics::vectorDir(degToRad(angleDirShip))*/;


        if (!m_enablePause) {
            m_ship.update(timeLoop * m_timeSpeed);
        }

        // Draw

        // Set view position
        if (m_enableFolowCamera) {
            currentView.setCenter(m_ship.kinematics().position());
        } else {
            currentView.setCenter(posView);
        }
        window->setView(currentView);

        // Draw view
        window->draw(*m_detailsView);

        // Draw vent apparent
        VectorView<float> ventAppView(apparentWind, "Va", sf::Color::Green);
        sf::Transform tApp;
        tApp.translate(m_ship.kinematics().position());
        window->draw(ventAppView, tApp);


        // Display information : 
        DisplayInfo::setZoom(zoomValue);
        DisplayInfo::setTopLeftPosition(posView - sf::Vector2f(SCREEN_WIDTH / 2 * zoomValue, SCREEN_HEIGHT / 2 * zoomValue));

        // Clocks infos
        DisplayInfo::draw(std::to_string(clockGlobal.getElapsedTime().asSeconds()));
        DisplayInfo::draw("fps : " + std::to_string(fps));

        // Data infos
        DisplayInfo::draw("ship :");
        DisplayInfo::draw("ship :" + std::to_string(shipDir));
        DisplayInfo::draw("acc : " + std::to_string(m_ship.kinematics().acceleration().x) + " " + std::to_string(m_ship.kinematics().acceleration().y));
        DisplayInfo::draw("speed : " + std::to_string(m_ship.kinematics().speed().x) + " " + std::to_string(m_ship.kinematics().speed().y));
        DisplayInfo::draw("pos : " + std::to_string(m_ship.kinematics().position().x) + " " + std::to_string(m_ship.kinematics().position().y));
        //        DisplayInfo::draw("dir : " + std::to_string(dir.x) + " " + std::to_string(dir.y) + ". norme : " + std::to_string(Kinematics::norme(m_ship.kinematics().speed())));

        //DisplayInfo::draw("wind : " + m_windView.force(m_ship.getPosition()).toString());

        // Draw infos
        DisplayInfo::draw("Wind Direction/Force: " + std::to_string(wind.direction()) + " " + std::to_string(wind.force()));
        DisplayInfo::draw("WindVector: " + std::to_string(windVector.x) + " " + std::to_string(windVector.y));
        DisplayInfo::draw("VentApparent : " + std::to_string(apparentWind.x) + " " + std::to_string(apparentWind.y));
        DisplayInfo::draw("sailVector : " + std::to_string(sailVector.x) + " " + std::to_string(sailVector.y));
        DisplayInfo::draw("helmVector : " + std::to_string(helmVector.x) + " " + std::to_string(helmVector.y));
        DisplayInfo::draw("ForceDePousser : " + std::to_string(forceDePousser.x) + " " + std::to_string(forceDePousser.y));


        if (clockFPS.getElapsedTime().asSeconds() >= 1) {
            fps = countFram;
            countFram = 0;
            clockFPS.restart();
        } else {
            ++countFram;
        }
        window->display();

    }

    m_tcpManager.disconnect();
}
