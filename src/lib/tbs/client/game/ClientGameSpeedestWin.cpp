/* 
 * File:   ClientGameSpeedestWin.cpp
 * Author: maxence
 * 
 * Created on 14 décembre 2014, 19:15
 */
#include <SFML/Window/Event.hpp>
#include <bitset>

#include "client/Client.h"
#include "client/DetailsView.h"
#include "client/GlobalView.h"
#include "client/game/ClientGameSpeedestWin.h"
#include "shared/network/MessageData.h"
#include "shared/network/MsgDisconnect.h"
#include "shared/network/MsgGame.h"
#include "shared/network/MsgTurnHelm.h"
#include "shared/network/MsgTurnSail.h"
#include "shared/network/MsgAction.h"

MsgGame& operator>>(MsgGame &msg, ClientGameSpeedestWin& game) {
    ClientWorld world;
    msg >> world;
    game.setClientWorld(world);

    return msg;
}

ClientGameSpeedestWin::ClientGameSpeedestWin(Client& client, ClientPlayer& player, sf::RenderWindow& window)
: m_world()
, m_client(client)
, m_player(player)
, m_window(window)
, m_enableFolowCamera(true)
, m_enablePause(false)
, m_timeSpeed(1.0f)
, m_zoomValue(1.0f)
, m_mainGraphic(nullptr)
, m_detailsView(nullptr)
, m_globalView(nullptr) {

}

ClientGameSpeedestWin::~ClientGameSpeedestWin() {
    release();
}

const ClientWorld& ClientGameSpeedestWin::getClientWorld() const {
    return m_world;
}

void ClientGameSpeedestWin::setClientWorld(const ClientWorld& world) {
    release();
    m_world = world;

}

void ClientGameSpeedestWin::release() {
    m_mainGraphic = nullptr;
    delete m_globalView;
    delete m_detailsView;
}

void ClientGameSpeedestWin::initGame() {

    Ship *s = &(m_world.getShips()[m_player.getId()]);
    s->initialize({1000, 1000}, {0, 0});
    m_world.setClientShip(s); // @TODO remove, it's temporary

    m_globalView = new GlobalView(m_world.getHeightMap(), m_world.getWindMap(), m_world.getClientShip());
    m_detailsView = new DetailsView(m_world);
    m_mainGraphic = dynamic_cast<sf::Drawable*> (m_detailsView);
    m_enableFolowCamera = true;
    //    m_posView = m_
    m_window.setKeyRepeatEnabled(true);
}

bool ClientGameSpeedestWin::startGameLoop() {
    sf::View currentView = m_window.getView();
    // Clocks
    sf::Clock clockGlobal;
    sf::Clock clockGameLoop;
    sf::Clock clockFPS;
    unsigned int counter = 0;
    int countFrames = 0;
    int fps = 0;
    std::bitset<4> keys;

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
                MsgDisconnect msgDiconnect;
                m_client.getNetwork().getUdpManager().send(msgDiconnect);
                m_window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                switch (event.key.code) {
                    case sf::Keyboard::Left:
                        m_posView.x -= 500.0f;
                        break;
                    case sf::Keyboard::Right:
                        m_posView.x += 500.0f;
                        break;
                    case sf::Keyboard::Up:
                        m_posView.y -= 500.0f;
                        break;
                    case sf::Keyboard::Down:
                        m_posView.y += 500.0f;
                        break;
                    case sf::Keyboard::Subtract:
                        m_zoomValue *= 2.0f;
                        currentView = sf::View(sf::FloatRect(m_posView.x, m_posView.y, SCREEN_WIDTH * m_zoomValue, SCREEN_HEIGHT * m_zoomValue));
                        break;
                    case sf::Keyboard::Add:
                        m_zoomValue /= 2.0f;
                        currentView = sf::View(sf::FloatRect(m_posView.x, m_posView.y, SCREEN_WIDTH * m_zoomValue, SCREEN_HEIGHT * m_zoomValue));
                        break;
                    case sf::Keyboard::D:
                    {
                        keys.set(TURN_HELM_POSITIVE, true);
                        /*MsgTurnHelm msgTurnHelmP(MsgOrientation::Positive);
                        m_client.getNetwork().getUdpManager().send(msgTurnHelmP);
                        m_world.getShip().setAngle(m_world.getShip().getAngle() + 5.0f);*/
                        m_world.getClientShip().setAngle(m_world.getClientShip().getAngle() + 5.0f);
                        m_world.getClientShip().getSail().setAngle(m_world.getClientShip().getSail().getAngle() + 5.0f);
                    }
                        break;
                    case sf::Keyboard::Q:
                    {
                        keys.set(TURN_HELM_NEGATIVE, true);
                        /*MsgTurnHelm msgTurnHelmN(MsgOrientation::Negative);
                        m_client.getNetwork().getUdpManager().send(msgTurnHelmN);
                        m_world.getShip().setAngle(m_world.getShip().getAngle() - 5.0f);*/

                        m_world.getClientShip().setAngle(m_world.getClientShip().getAngle() - 5.0f);
                        m_world.getClientShip().getSail().setAngle(m_world.getClientShip().getSail().getAngle() - 5.0f);
                    }
                        break;
                    case sf::Keyboard::Z:
                    {
                        keys.set(TURN_SAIL_POSITIVE, true);
                        /* MsgTurnSail msgTurnSailP(MsgOrientation::Positive);
                         m_client.getNetwork().getUdpManager().send(msgTurnSailP);
                         m_world.getShip().getSail().setAngle(m_world.getShip().getSail().getAngle() + 5.0f);*/
                    }
                        break;

                    case sf::Keyboard::S:
                    {
                        keys.set(TURN_SAIL_NEGATIVE, true);
                        /* MsgTurnSail msgTurnSailN(MsgOrientation::Negative);
                         m_client.getNetwork().getUdpManager().send(msgTurnSailN);
                         m_world.getShip().getSail().setAngle(m_world.getShip().getSail().getAngle() - 5.0f);*/
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
            } else if (event.type == sf::Event::KeyReleased) {
                switch (event.key.code) {
                    case sf::Keyboard::D:
                        keys.set(TURN_HELM_POSITIVE, false);
                        break;
                    case sf::Keyboard::Q:
                        keys.set(TURN_HELM_NEGATIVE, false);
                        break;
                    case sf::Keyboard::Z:
                        keys.set(TURN_SAIL_POSITIVE, false);
                        break;
                    case sf::Keyboard::S:
                        keys.set(TURN_SAIL_NEGATIVE, false);
                        break;
                    default:
                        break;
                }
            }
        }

        counter++;
        if (counter % 30 == 0) {
            counter = 0;
            MessageData msg;
            msg << MsgType::Action << static_cast<sf::Uint8> (keys.to_ulong());
            m_client.getNetwork().getUdpManager().send(msg);
        }

        m_client.pollMessages();

        // Set view position
        if (m_enableFolowCamera) {
            currentView.setCenter(m_world.getClientShip().kinematics().position());
        } else {
            currentView.setCenter(m_posView);
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
            currentView.setCenter(m_world.getClientShip().kinematics().position());
        } else {
            currentView.setCenter(m_posView);
        }
        m_window.setView(currentView);

        // Draw view
        m_window.draw(*m_mainGraphic);

        if (clockFPS.getElapsedTime().asSeconds() >= 1) {
            fps = countFrames;
            countFrames = 0;
            clockFPS.restart();
        } else {
            ++countFrames;
        }
        m_window.display();

    }

    return m_window.isOpen();
}

bool ClientGameSpeedestWin::readGameInfo(MessageData& msg) {
    std::cout << "GameInfo" << std::endl;
    while (msg) {
        sf::Uint8 id;
        float shipAngle;
        float sailAngle;
        float positionX;
        float positionY;
        float speedX;
        float speedY;

        msg >> id >> shipAngle >> sailAngle >> positionX >> positionY >> speedX >> speedY;

        Ship &ship = m_world.getShips()[static_cast<unsigned int> (id)];
        ship.setAngle(shipAngle);
        ship.getSail().setAngle(shipAngle);
        ship.kinematics().position() = {positionX, positionY};
        ship.kinematics().speed() = {speedX, speedY};
        std::cout << "Recv ship(" << static_cast<unsigned int> (id) << ") pos(" << positionX << "," << positionY << ") speed(" << speedX << "," << speedY << ")" << std::endl;
    }
    return true;
}

bool ClientGameSpeedestWin::read(MessageData& msg) {
    MsgType msgType;
    msg >> msgType;
    switch (msgType) {
        case MsgType::GameInfo:
            return readGameInfo(msg);
        default:
            return false;
    }
}

bool ClientGameSpeedestWin::readInitGame(MessageData& msg) {
    sf::Int32 width, height, seedHeight, seedWind;
    msg >> width >> height >> seedHeight >> seedWind;
    ClientWorld world;
    std::cout << "RECEIVE map(" << width << ", " << height << ", " << seedHeight << ", " << seedWind << ")" << std::endl;
    world.initializeMap(width, height, seedHeight, seedWind);
    world.initialize();
    setClientWorld(world);
    return true;
}
