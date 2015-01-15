/* 
 * File:   ClientGameSpeedestWin.cpp
 * Author: maxence
 * 
 * Created on 14 décembre 2014, 19:15
 */
#include <SFML/Window/Event.hpp>

#include "client/Client.h"
#include "client/DetailsView.h"
#include "client/GlobalView.h"
#include "client/game/ClientGameSpeedestWin.h"
#include "shared/network/MsgData.h"
#include "shared/network/MsgDisconnect.h"
#include "shared/network/MsgGame.h"
#include "shared/network/MsgTurnHelm.h"
#include "shared/network/MsgTurnSail.h"
#include "shared/network/MsgAction.h"
#include "client/game/ClientGameConnection.h"

ClientGameSpeedestWin::ClientGameSpeedestWin(sf::RenderWindow& window, Client& client, ClientPlayer& player)
: ClientGame(window, client)
, m_world()
, m_player(player)
, m_enableFolowCamera(true)
, m_enablePause(false)
, m_timeSpeed(1.0f)
, m_zoomValue(1.0f)
, m_mainGraphic(nullptr)
, m_detailsView(nullptr)
, m_globalView(nullptr)
, m_currentView(m_window.getView()) {
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

void ClientGameSpeedestWin::init() {
    m_globalView = new GlobalView(m_world.getHeightMap(), m_world.getWindMap(), m_world.getClientShip());
    m_detailsView = new DetailsView(m_world);
    m_mainGraphic = dynamic_cast<sf::Drawable*> (m_detailsView);
    m_enableFolowCamera = true;
    m_window.setKeyRepeatEnabled(false);
}

void ClientGameSpeedestWin::update(float dt) {
    // Update world
    if (!m_enablePause) {
        m_world.update(dt * m_timeSpeed);
    }
}

void ClientGameSpeedestWin::draw() {
    
    if(&(m_world.getClientShip()) == nullptr)
        return;
    
    // Set view position
    if (m_enableFolowCamera) {
        m_currentView.setCenter(m_world.getClientShip().kinematics().position());
    } else {
        m_currentView.setCenter(m_posView);
    }
    m_window.setView(m_currentView);

    // Draw view
    if (m_mainGraphic)
        m_window.draw(*m_mainGraphic);
}

bool ClientGameSpeedestWin::isEnded() {
    return false;
}

void ClientGameSpeedestWin::sendInfo() {
    MsgData msg;
    msg << MsgType::Action << static_cast<sf::Uint8> (m_keys.to_ulong()) << m_clockGame.getElapsedTime().asMilliseconds();
    m_client.getNetwork().getUdpManager().send(msg);
}

bool ClientGameSpeedestWin::read(sf::Event& event) {
    if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
        m_window.close();
    }
    else if(event.type == sf::Event::Resized) {
        m_currentView.setSize(event.size.width * m_zoomValue, event.size.height * m_zoomValue);
    }
    else if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
            case sf::Keyboard::Left:
                m_posView.x -= 255.0f * m_zoomValue;
                break;
            case sf::Keyboard::Right:
                m_posView.x += 255.0f * m_zoomValue;
                break;
            case sf::Keyboard::Up:
                m_posView.y -= 255.0f * m_zoomValue;
                break;
            case sf::Keyboard::Down:
                m_posView.y += 255.0f * m_zoomValue;
                break;
            case sf::Keyboard::Subtract:
                m_zoomValue *= 2.0f;
                m_currentView.setSize(m_window.getSize().x * m_zoomValue, m_window.getSize().y * m_zoomValue);
                break;
            case sf::Keyboard::Add:
                m_zoomValue /= 2.0f;
                m_currentView = sf::View(m_posView, sf::Vector2f(m_window.getSize().x * m_zoomValue, m_window.getSize().y * m_zoomValue));
                break;
            case sf::Keyboard::D:
            {
                m_keys.set(TURN_HELM_POSITIVE, true);
                m_hasInfoToSend = true;
            }
                break;
            case sf::Keyboard::Q:
            {
                m_keys.set(TURN_HELM_NEGATIVE, true);
                m_hasInfoToSend = true;
            }
                break;
            case sf::Keyboard::Z:
            {
                m_keys.set(TURN_SAIL_POSITIVE, true);
                m_hasInfoToSend = true;
            }
                break;

            case sf::Keyboard::S:
            {
                m_keys.set(TURN_SAIL_NEGATIVE, true);
                m_hasInfoToSend = true;
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
                return false;
        }
    } else if (event.type == sf::Event::KeyReleased) {
        switch (event.key.code) {
            case sf::Keyboard::D:
                m_keys.set(TURN_HELM_POSITIVE, false);
                m_hasInfoToSend = true;
                break;
            case sf::Keyboard::Q:
                m_keys.set(TURN_HELM_NEGATIVE, false);
                m_hasInfoToSend = true;
                break;
            case sf::Keyboard::Z:
                m_keys.set(TURN_SAIL_POSITIVE, false);
                m_hasInfoToSend = true;
                break;
            case sf::Keyboard::S:
                m_keys.set(TURN_SAIL_NEGATIVE, false);
                m_hasInfoToSend = true;
                break;
            default:
                return false;
        }
    }
    return true;
}

bool ClientGameSpeedestWin::read(MsgData & msg) {
    m_ping = m_clockPing.getElapsedTime();
    
    MsgType msgType;
    msg >> msgType;
    switch (msgType) {
        case MsgType::Game:
            return readInitGame(msg);
        case MsgType::GameInfo:
            return readGameInfo(msg);
        case MsgType::Disconnect:
            return readDisconnect(msg);
        case MsgType::Checkpoint:
            return readCheckpoint(msg);
        default:
            return false;
    }
}

bool ClientGameSpeedestWin::readInitGame(MsgData & msg) {
    sf::Int32 width, height, seedHeight, seedWind;
    sf::Int32 checkPointCount;
    sf::Int32 shipCount;
    msg >> height >> width >> seedHeight >> seedWind;
    
    m_world.initialize();
    std::cout << "RECEIVE map(" << height << ", " << width << ", " << seedHeight << ", " << seedWind << ")" << std::endl;
    m_world.initializeMap(width, height, seedHeight, seedWind);
    
    msg >> checkPointCount;
    for (int i = 0; i < checkPointCount; ++i) {
        sf::Vector2i posCheckPoint;
        msg >> posCheckPoint.x >> posCheckPoint.y;
        
        m_world.addCheckPoint(posCheckPoint);
    }
    
    msg >> shipCount;
    
    for(int i = 0; i < shipCount; ++i) {
        sf::Uint8 id;
        msg >> id;
        Ship& ship = m_world.getShips()[static_cast<unsigned int>(id)];
        auto& shipPos = ship.kinematics().position();
        msg >> shipPos.x >> shipPos.y;
        ship.setAngle(90.0f);
        ship.getSail().setAngle(m_world.getWindMap().wind(shipPos.x / TILE_SIZE, shipPos.y / TILE_SIZE).getDirection());
    }
    
    return true;
}

bool ClientGameSpeedestWin::readGameInfo(MsgData & msg) {
    std::cout << "GameInfo" << std::endl;
    sf::Int32 time;
    msg >> time;
    if (!MsgData::checkValidity(sf::milliseconds(time), m_lastGameInfo))
        return false;

    while (!msg.endOfPacket()) {

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
        ship.getSail().setAngle(sailAngle);
        ship.kinematics().position() = {positionX, positionY};
        ship.kinematics().speed() = {speedX, speedY};
        std::cout << "Recv ship(" << static_cast<unsigned int> (id) << ") pos(" << positionX << "," << positionY << ") speed(" << speedX << "," << speedY << ")" << std::endl;
    }
    m_world.setClientShip(&m_world.getShips()[m_player.getId()]);
    return true;
}

bool ClientGameSpeedestWin::readDisconnect(MsgData & msg) {
    sf::Uint8 id;
    msg >> id;
    std::cout << m_world.getShips().erase(static_cast<unsigned int> (id)) << std::endl;
    m_detailsView->updateShips();
    std::cout << "Ship of player " << static_cast<unsigned int> (id) << " remove and view update" << std::endl;
    return true;
}

bool ClientGameSpeedestWin::readCheckpoint(MsgData& msg) {
    sf::Uint8 idCheckpoint;
    
    msg >> idCheckpoint;
    
    m_world.getCheckPointManager().getCheckPoint(idCheckpoint).activate();
    return true;
}
