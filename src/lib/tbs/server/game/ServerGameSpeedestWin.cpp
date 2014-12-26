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
#include "shared/network/MessageData.h"
#include "shared/ship/Ship.h"

#include "server/ServerPlayer.h"
#include "server/ServerPlayers.h"
#include "server/game/ServerGameSpeedestWin.h"

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
    // @TODO
}

void ServerGameSpeedestWin::update(float dt) {
    for (auto& test : m_ships) {
        updateShipVelocity(test.second);
        test.second.update(dt);
    }
}

void ServerGameSpeedestWin::updateShipVelocity(Ship& ship) {
    Wind wind = m_map.getWind(static_cast<sf::Vector2i> (ship.kinematics().position() / sf::Vector2f(TILE_SIZE, TILE_SIZE)));

    sf::Vector2f shipVector = ship.kinematics().speed();
    sf::Vector2f windVector = wind.getVector();

    sf::Vector2f apparentWind = windVector - shipVector;

    float windAngle = Kinematics::direction(windVector);
    float apparentWindAngle = Kinematics::direction(apparentWind);
    float sailAngle = ship.getSail().getAngle();

    std::cout << "angle : " << std::abs(windAngle - sailAngle) << std::endl;
    float angleToRad = Kinematics::degToRad(std::abs(windAngle - sailAngle));

    //sf::Vector2f F = 0.1f * apparentWind * apparentWind * std::sin(Kinematics::degToRad(sailAngle));
    sf::Vector2f P = {std::cos(Kinematics::degToRad(ship.getAngle())), std::sin(Kinematics::degToRad(ship.getAngle()))};
    sf::Vector2f F = 0.1f * apparentWind * apparentWind * std::sin(angleToRad);

    sf::Vector2f Fm = (F.x * P.x + F.y * P.y) * P;
    //sf::Vector2f F = 10.0f * windVector * std::sin(angleToRad) * std::sin(angleToRad);

    // somme des forces = ma
    // v = a*t + v0
    // x = (1/2) * a.x * t * t + v0.x * t + x0
    // y = (1/2) * a.y * t * t + v0.y * t + y0

    //m_ship.kinematics().speed() = windVector /* Kinematics::vectorDir(degToRad(angleDirShip))*/;
    ship.kinematics().speed() = Fm;

}

bool ServerGameSpeedestWin::gameIsEnded() {
    return false;
}

void ServerGameSpeedestWin::sendInfo() {
    // @TODO
}

sf::Packet ServerGameSpeedestWin::toPacket(sf::Packet &packet) const {
    return packet << m_map;
}

bool ServerGameSpeedestWin::read(MessageData& message, ServerPlayer& player) {
    /*MsgType msgType;
    message >> msgType;
    switch (msgType) {
        case MsgType::ActionTurnHelm:
            readTurnHelm(message);
            break;
        case MsgType::ActionTurnSail:
            readTurnSail(message);
            break;
        default:
            return false;
    }*/
    return true;
    // @TODO delete message, use unique_ptr ?
}

void ServerGameSpeedestWin::readTurnHelm(MessageData& msg) {
    std::cout << "Turn Helm ";

    MsgOrientation orientation;
    float angle;
    msg >> orientation >> angle;

    if (orientation == MsgOrientation::Positive)
        std::cout << "Positive(" << angle << ")" << std::endl;
    else if (orientation == MsgOrientation::Negative)
        std::cout << "Negative(" << angle << ")" << std::endl;
    else
        std::cout << "undefined(WARNING)" << std::endl;
}

void ServerGameSpeedestWin::readTurnSail(MessageData& msg) {
    std::cout << "Turn Sail ";
    sf::Int8 sfOrientation;
    float angle;
    msg >> sfOrientation >> angle;
    MsgOrientation orientation = static_cast<MsgOrientation> (sfOrientation);
    if (orientation == MsgOrientation::Positive)
        std::cout << "Positive(" << angle << ")" << std::endl;
    else if (orientation == MsgOrientation::Negative)
        std::cout << "Negative(" << angle << ")" << std::endl;
    else
        std::cout << "undefined(WARNING)" << std::endl;
}
