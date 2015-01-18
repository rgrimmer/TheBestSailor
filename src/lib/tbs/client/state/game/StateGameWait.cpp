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
#include "client/state/game/GameStateManager.h"
#include "client/state/game/StateGameWait.h"
#include "client/state/game/StateGame.h"

StateGameWait::StateGameWait(GameStateManager& manager, ClientNetwork& network, ClientPlayer& player, ClientWorld& world)
: State()
, m_manager(manager)
, m_network(network)
, m_player(player)
, m_world(world) {
}

StateGameWait::~StateGameWait() {

}

void StateGameWait::initialize(void) {
}

void StateGameWait::release(void) {
}

void StateGameWait::activate(void) {
    std::cout << "[WaitGame][Activate]" << std::endl;
}

void StateGameWait::deactivate(void) {
    std::cout << "[WaitGame][Deactivate]" << std::endl;
}

void StateGameWait::update(float dt) {
}

void StateGameWait::render(sf::RenderWindow& window) const {
    window.clear(sf::Color(52,23,120));
}

bool StateGameWait::read(sf::Event& event) {

    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape) {
            m_manager.getManager().pop();
        }
    } else if (event.type == sf::Event::Closed) {
        return false;
    }

    return true;
}

bool StateGameWait::read(MsgData& msg) {
    MsgType msgType;
    msg >> msgType;
    switch (msgType) {
        case MsgType::Game:
            return readInitGame(msg);

        default:
            return true;
    }
}

bool StateGameWait::readInitGame(MsgData & msg) {
    GameType gameType;
    sf::Int32 width, height, seedHeight, seedWind;
    sf::Int32 checkPointCount;
    sf::Int32 shipCount;
    msg >> gameType >> height >> width >> seedHeight >> seedWind;

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

    for (int i = 0; i < shipCount; ++i) {
        sf::Uint8 id;
        msg >> id;
        Ship& ship = m_world.getShips()[static_cast<unsigned int> (id)];
        auto& shipPos = ship.kinematics().position();
        msg >> shipPos.x >> shipPos.y;
        ship.setAngle(90.0f);
        ship.getSail().setAngle(m_world.getWindMap().wind(static_cast<sf::Vector2i> (shipPos)).getDirection());
    }
    m_world.setClientShip(&m_world.getShips()[m_player.getId()]);
    m_manager.push(EGameStateManager::Started);
    return true;
}