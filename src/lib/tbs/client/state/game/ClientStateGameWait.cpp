/* 
 * File:   StateGameWait.cpp
 * Author: maxence
 * 
 * Created on 16 janvier 2015, 23:28
 */

#include "shared/game/GameType.h"

#include "shared/network/MsgData.h"
#include "shared/network/MsgType.h"

#include "client/ClientWorld.h"
#include "client/ClientPlayer.h"

#include "client/network/ClientNetwork.h"

#include "client/state/ClientState.h"
#include "client/state/game/ClientStateGame.h"
#include "client/state/game/ClientStateGameWait.h"

ClientStateGameWait::ClientStateGameWait(ClientStateGame& manager, ClientNetwork& network, ClientPlayer& player, ClientWorld& world)
: State()
, m_manager(manager)
, m_network(network)
, m_player(player)
, m_world(world) {
}

ClientStateGameWait::~ClientStateGameWait() {

}

void ClientStateGameWait::initialize(void) {
}

void ClientStateGameWait::release(void) {
}

void ClientStateGameWait::activate(void) {
    std::cout << "[GameWait][Activate]" << std::endl;
}

void ClientStateGameWait::deactivate(void) {
    std::cout << "[GameWait][Deactivate]" << std::endl;
}

void ClientStateGameWait::update(float dt) {
    //    std::cout << "[GameWait][Update]" << std::endl;
    m_view.decreaseTimeLeft(dt);
}

void ClientStateGameWait::render(sf::RenderWindow& window) const {
    window.draw(m_view);
}

bool ClientStateGameWait::read(sf::Event& event) {

    if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
            case sf::Keyboard::Escape:
                m_manager.getManager().pop();
                break;

            default:
            {
                MsgData msg;
                msg << MsgType::Action << sf::Int16(event.key.code);
                m_network.getTcpManager().send(msg);
            }
                break;
        }
    } else if (event.type == sf::Event::Closed) {
        return false;
    }

    return true;
}

bool ClientStateGameWait::read(MsgData& msg) {
    MsgType msgType;
    msg >> msgType;
    switch (msgType) {
        case MsgType::Game:
            return readInitGame(msg);
        case MsgType::TimeLeft:
            return readTimeLeft(msg);

        default:
            return true;
    }
}

bool ClientStateGameWait::readInitGame(MsgData & msg) {
    GameType gameType;
    sf::Int32 width, height, seedHeight, seedWind;
    sf::Int32 checkPointCount;
    sf::Int32 shipCount;
    msg >> gameType >> height >> width >> seedHeight >> seedWind;

    m_world.initialize();
    std::cout << "[GameWait][Read] \tmap(" << height << ", " << width << ", " << seedHeight << ", " << seedWind << ")" << std::endl;
    m_world.initializeMap(width, height, seedHeight, seedWind);

    msg >> checkPointCount;
    for (int i = 0; i < checkPointCount; ++i) {
        sf::Vector2i posCheckPoint;
        msg >> posCheckPoint.x >> posCheckPoint.y;

        m_world.addCheckPoint(posCheckPoint);
    }

    msg >> shipCount;

    for (int i = 0; i < shipCount; ++i) {
        sf::Uint8 id;
        msg >> id;
        Ship& ship = m_world.getShips()[static_cast<unsigned int> (id)];
        msg >> ship.position().x >> ship.position().y;
        ship.setAngle(90.0f);
        ship.getSail().setAngle(m_world.getWindMap().wind(static_cast<sf::Vector2i> (ship.position())).getDirection());
    }
    m_world.setClientShip(&m_world.getShips()[m_player.getId()]);
    m_manager.push(EStateGame::Started);
    return true;
}

bool ClientStateGameWait::readTimeLeft(MsgData& msg) {
    float timeLeft;
    msg >> timeLeft;

    m_view.setTimeLeft(timeLeft);

    std::cout << "[GameWait][Read]\t leftTime(" << static_cast<int> (timeLeft) << ")" << std::endl;
    return true;
}
