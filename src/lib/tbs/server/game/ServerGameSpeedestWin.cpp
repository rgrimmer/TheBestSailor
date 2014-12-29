/* 
 * File:   ServerGameSpeedestWin.cpp
 * Author: maxence
 * 
 * Created on 13 décembre 2014, 11:19
 */
#include <iostream>

#include "shared/Utils.h"
#include "shared/network/MsgTurnHelm.h"
#include "shared/network/MsgTurnSail.h"
#include "shared/network/MsgDisconnect.h"
#include "shared/network/MsgAction.h"
#include "shared/network/MessageData.h"
#include "shared/ship/Ship.h"

#include "server/ServerPlayer.h"
#include "server/ServerPlayers.h"
#include "server/Server.h"
#include "server/game/ServerGameSpeedestWin.h"
#include "server/network/ServerNetwork.h"

sf::Vector2f operator*(const sf::Vector2f &v1, const sf::Vector2f &v2) {
    return sf::Vector2f(v1.x * v2.x, v1.y * v2.y);
}

sf::Vector2f operator*(const sf::Vector2f &v1, float coef) {
    return sf::Vector2f(v1.x * coef, v1.y * coef);
}

sf::Vector2f operator/(const sf::Vector2f &v1, const sf::Vector2f &v2) {
    return sf::Vector2f(v1.x / v2.x, v1.y / v2.y);
}

sf::Packet& operator<<(sf::Packet& packet, const ServerGameSpeedestWin& game) {
    return packet << game.getMap();
}

ServerGameSpeedestWin::ServerGameSpeedestWin(Server &server, ServerPlayers& players, const MapHeader &header)
: ServerGame(server, players)
, m_map(header) {


}

ServerGameSpeedestWin::~ServerGameSpeedestWin() {
}

const Map& ServerGameSpeedestWin::getMap() const {
    return m_map;
}

void ServerGameSpeedestWin::init() {
    sf::Vector2f position(1000.0f, 1000.0f);
    for (auto* player : m_players.inGame()) {
        Ship ship;
        ship.kinematics().position() = position;
        ship.setAngle(90.0f);
        m_ships[player] = ship;
        position.x += 32.0f;
    }
    sendInfo();
}

void ServerGameSpeedestWin::update(float dt) {
    for (auto& test : m_ships) {
        updateShipState(test.second, dt);
        updateSail(test.second);
        updateShipVelocity(test.second);
        test.second.update(dt);
    }
}

void ServerGameSpeedestWin::updateShipState(Ship& ship, float dt) {
    if (ship.isTurningNegative()) {
        ship.turnNegative(45.0f * dt);
        ship.getSail().turnNegative(45.0f * dt);
    }
    if (ship.isTurningPositive()) {
        ship.turnPositive(45.0f * dt);
        ship.getSail().turnPositive(45.0f * dt);
    }
    if (ship.getSail().isTurningNegative()) {
        ship.getSail().turnNegative(45.0f * dt);
    }
    if (ship.getSail().isTurningPositive()) {
        ship.getSail().turnPositive(45.0f * dt);
    }
}

void ServerGameSpeedestWin::updateSail(Ship& ship) {
    Wind wind = m_map.getWind(static_cast<sf::Vector2i> (ship.kinematics().position() / sf::Vector2f(TILE_SIZE, TILE_SIZE)));
    float angleShip = ship.getAngle();
    float diff = 360.0f - angleShip;
    float windDir = wind.getDirection() + diff;
    if (windDir >= 360.0f)
        windDir -= 360.0f;
    float sailDir = ship.getSail().getAngle() + diff;
    if (sailDir >= 360.0f)
        sailDir -= 360.0f;

    float diffSailWind = sailDir - windDir;
    if (windComeFromTribord(ship, wind)) {
        if (sailDir < 180.0f)
            ship.getSail().setAngle(ship.getSail().getAngle() + (180.0f - sailDir)*2.0f);
        if (diffSailWind > 0.0f)
            ship.getSail().setAngle(ship.getSail().getAngle() - diffSailWind);

    } else {
        if (sailDir > 180.0f)
            ship.getSail().setAngle(ship.getSail().getAngle() - (sailDir - 180.0f)*2.0f);
        if (diffSailWind < 0.0f)
            ship.getSail().setAngle(ship.getSail().getAngle() - diffSailWind);
    }
}

void ServerGameSpeedestWin::updateShipVelocity(Ship& ship) {
    Wind wind = m_map.getWind(static_cast<sf::Vector2i> (ship.kinematics().position() / sf::Vector2f(TILE_SIZE, TILE_SIZE)));
    float shipDirRad = Kinematics::degToRad(ship.getAngle());
    sf::Vector2f outP(std::cos(shipDirRad), std::sin(shipDirRad));

    // Temporary equation 
    sf::Vector2f windForce = wind.getVector() * std::sin(Kinematics::degToRad(std::abs(ship.getSail().getAngle() - wind.getDirection())));
    sf::Vector2f velocity = std::sqrt(windForce.x * windForce.x + windForce.y * windForce.y) * outP;
    ship.kinematics().speed() = velocity;
}

bool ServerGameSpeedestWin::windComeFromFront(const Ship& ship, const Wind& wind) const {
    return (static_cast<int> (450 - ship.getAngle() + wind.getDirection()) % 360 > 180);
}

bool ServerGameSpeedestWin::windComeFromTribord(const Ship& ship, const Wind& wind) const {
    return (static_cast<int> (360 - ship.getAngle() + wind.getDirection()) % 360 > 180);
}

bool ServerGameSpeedestWin::gameIsEnded() {
    return m_players.inGame().size() == 0;
}

void ServerGameSpeedestWin::sendInfo() {
    // @TODO
    MessageData msgGameInfo;
    msgGameInfo << MsgType::GameInfo;

    sf::Uint8 id;
    float shipAngle;
    float sailAngle;
    float positionX;
    float positionY;
    float speedX;
    float speedY;

    for (auto& ship : m_ships) {
        id = ship.first->getId();
        shipAngle = ship.second.getAngle();
        sailAngle = ship.second.getSail().getAngle();
        sf::Vector2f posShip = ship.second.kinematics().position();
        positionX = posShip.x;
        positionY = posShip.y;
        sf::Vector2f speedShip = ship.second.kinematics().speed();
        speedX = speedShip.x;
        speedY = speedShip.y;
        msgGameInfo << id << shipAngle << sailAngle << positionX << positionY << speedX << speedY;
        std::cout << "Send ship(" << static_cast<unsigned int> (id) << ") pos(" << positionX << "," << positionY << ") speed(" << speedX << "," << speedY << ")" << std::endl;
    }

    m_server.getNetwork()->getUDPManager().send(msgGameInfo, m_players.inGame());
}

sf::Packet ServerGameSpeedestWin::toPacket(sf::Packet &packet) const {
    return packet << m_map;
}

bool ServerGameSpeedestWin::read(MessageData& message, ServerPlayer& player) {
    MsgType msgType;
    message >> msgType;

    switch (msgType) {
        case MsgType::Action:
            return readAction(message, player);
        case MsgType::Disconnect:
            return readDisconnect(message, player);
        default:
            return false;
    }
    // @TODO delete message, use unique_ptr ?
}

bool ServerGameSpeedestWin::readDisconnect(MessageData& msg, ServerPlayer& player) {
    std::cout << "Remove " << m_ships.erase(&player) << " ship" << std::endl;
    for (auto& ship : m_ships) {
        std::cout << "Stay ship of " << ship.first->getId() << " " << ship.first->getName() << std::endl;
    }
    return true;
}

bool ServerGameSpeedestWin::readAction(MessageData& msg, ServerPlayer& player) {
    sf::Uint8 keysUI8;
    msg >> keysUI8;
    std::bitset<4> keys = keysUI8;

    m_ships[&player].setTurningNegative(keys.test(TURN_HELM_NEGATIVE));
    m_ships[&player].setTurningPositive(keys.test(TURN_HELM_POSITIVE));
    m_ships[&player].getSail().setTurningNegative(keys.test(TURN_SAIL_NEGATIVE));
    m_ships[&player].getSail().setTurningPositive(keys.test(TURN_SAIL_POSITIVE));

    return true;
}
