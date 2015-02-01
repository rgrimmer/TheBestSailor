/* 
 * File:   ServerGameSpeedestWin.cpp
 * Author: maxence
 * 
 * Created on 13 décembre 2014, 11:19
 */
#include <iostream>

#include "shared/game/GameType.h"
#include "shared/Utils.h"
#include "shared/network/MsgTurnHelm.h"
#include "shared/network/MsgTurnSail.h"
#include "shared/network/MsgDisconnect.h"
#include "shared/network/MsgAction.h"
#include "shared/network/MsgData.h"
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
    m_checkPointManager.initialise(m_map.getHeightMap());
    sf::Vector2f initPosition = static_cast<sf::Vector2f> (m_checkPointManager.getCheckPoint(0).getPosition());
    initPosition.x += 0.25f;
    sf::Vector2f position(initPosition);
    int count = 0;
    for (auto* player : m_players.inGame()) {
        // Set Ship
        m_ships[player] = Ship(position, 90.0f, m_map.getWind(static_cast<sf::Vector2i> (position)).direction(), player->getShipType());
        // Set next pos
        position.x += 0.25f;
        count++;
        if (count >= 4) {
            position.x = initPosition.x;
            position.y += 0.25f;
            count = 0;
        }
    }
}

ServerGameSpeedestWin::ServerGameSpeedestWin(const ServerGameSpeedestWin& other) :
ServerGameSpeedestWin(other.m_server, m_players, m_map.getHeader()) {
}

ServerGameSpeedestWin::~ServerGameSpeedestWin() {
}

const Map& ServerGameSpeedestWin::getMap() const {
    return m_map;
}

void ServerGameSpeedestWin::init() {
}

void ServerGameSpeedestWin::update(float dt) {
    if (m_endGameStarted) {
        if (m_endGameClock.getElapsedTime() >= sf::seconds(6)) {
            m_players.putPlayersInGameToInWait();
        }
    } else {
        for (auto* player : m_players.inGame()) {
            if (m_checkPointManager.isCompletedAllCheckpoint(player)) {
                m_endGameStarted = true;
                m_endGameClock.restart();
                MsgData msg;
                msg << MsgType::GameEnd << player->getName();
                m_server.getNetwork()->getTCPManager().send(msg, m_players.inGame());
            }
        }
    }
    for (auto& ship : m_ships) {
        updateSail(ship.second);
        sf::Vector2f shipVelocity = calculShipVelocity(ship.second);

        if (collideWithMap(ship.second, shipVelocity))
            shipVelocity = {0.0f, 0.0f};

        ship.second.setVelocity(shipVelocity);

        int checkPointCount = m_checkPointManager.getCheckPointCount();

        for (int i = 0; i < checkPointCount; i++) {
            ServerCheckpoint c = m_checkPointManager.getCheckPoint(i);
            if (!m_checkPointManager.isCompletedCheckpoint(ship.first, i)) {
                if (collideWithCheckPoint(ship.second, c)) {
                    m_checkPointManager.addCompletedCheckpoint(ship.first, i);
                    MsgData msgCheckpoint;
                    msgCheckpoint << MsgType::Checkpoint << static_cast<sf::Uint8> (i);
                    m_server.getNetwork()->getTCPManager().send(msgCheckpoint, ship.first->getTCPSocket());
                }
            }
        }

        ship.second.update(dt);
    }
}

void ServerGameSpeedestWin::updateSail(Ship& ship) {
    Wind wind = m_map.getWind(static_cast<sf::Vector2i> (ship.getPosition()));
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

sf::Vector2f ServerGameSpeedestWin::calculShipVelocity(Ship& ship) {
    Wind wind = m_map.getWind(static_cast<sf::Vector2i> (ship.getPosition()));
    float shipDirRad = Kinematics::degToRad(ship.getAngle());
    sf::Vector2f outP(std::cos(shipDirRad), std::sin(shipDirRad));

    // Temporary equation 
    sf::Vector2f windForce = wind.getVector() * std::sin(Kinematics::degToRad(std::abs(ship.getSail().getAngle() - wind.getDirection())));
    sf::Vector2f velocity = std::sqrt(windForce.x * windForce.x + windForce.y * windForce.y) * outP;
    return velocity;
}

bool ServerGameSpeedestWin::collideWithMap(const Ship & ship, const sf::Vector2f & velocity) {
    int x = (ship.getPosition().x + velocity.x);
    int y = (ship.getPosition().y + velocity.y);
    return !WATER(m_map.getHeightMap().getValue(x, y));
}

bool ServerGameSpeedestWin::collideWithCheckPoint(const Ship & ship, const ServerCheckpoint & checkPoint) {

    return (static_cast<sf::Vector2i> (ship.getPosition()) == checkPoint.getPosition());
}

bool ServerGameSpeedestWin::windComeFromFront(const Ship& ship, const Wind& wind) const {
    return (static_cast<int> (450 - ship.getAngle() + wind.getDirection()) % 360 > 180);
}

bool ServerGameSpeedestWin::windComeFromTribord(const Ship& ship, const Wind& wind) const {
    return (static_cast<int> (360 - ship.getAngle() + wind.getDirection()) % 360 > 180);
}

bool ServerGameSpeedestWin::gameIsEnded() {
    std::cout << "Nb players in game(" << m_players.inGame().size() << ")" << std::endl;
    return m_players.inGame().size() == 0;
}

void ServerGameSpeedestWin::sendGame() {
    MsgData msgGame;
    msgGame << MsgType::Game << GameType::SpeedestWin
            << sf::Int32(m_map.getHeader().getHeight())
            << sf::Int32(m_map.getHeader().getWidth())
            << sf::Int32(m_map.getHeightMap().getSeed())
            << sf::Int32(m_map.getWindMap().getSeed());

    // Send checkpoint
    msgGame << sf::Int32(m_checkPointManager.getCheckPointCount());

    for (auto& checkpoint : m_checkPointManager.getCheckPoints()) {
        sf::Vector2i position = checkpoint.getPosition();
        msgGame << sf::Int32(position.x) << sf::Int32(position.y);
    }

    // Send ship
    msgGame << sf::Int32(m_ships.size());

    for (auto& pair : m_ships) {
        auto& ship = pair.second;
        msgGame << static_cast<sf::Uint8> (pair.first->getId())
                << static_cast<sf::Uint8> (ship.getType())
                << ship.getPosition().x
                << ship.getPosition().y;
    }

    m_server.getNetwork()->getTCPManager().send(msgGame, std::vector<ServerPlayer*>(m_players.inGame().begin(), m_players.inGame().end()));
}

void ServerGameSpeedestWin::sendInfo(ServerPlayer& player, sf::Uint32 idReq) {

    MsgData msgGameInfo;
    msgGameInfo << MsgType::GameInfo << idReq;

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
        const sf::Vector2f& posShip = ship.second.getPosition();
        positionX = posShip.x;
        positionY = posShip.y;
        const sf::Vector2f& speedShip = ship.second.getVelocity();
        speedX = speedShip.x;
        speedY = speedShip.y;
        msgGameInfo << id << shipAngle << sailAngle << positionX << positionY << speedX << speedY;
        std::cout << "Send ship(" << static_cast<unsigned int> (id) << ") pos(" << positionX << "," << positionY << ") speed(" << speedX << "," << speedY << ") id(" << idReq << ")" << std::endl;
    }

    m_server.getNetwork()->getUDPManager().send(msgGameInfo, player);
}

bool ServerGameSpeedestWin::read(MsgData& message, ServerPlayer& player) {
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
}

bool ServerGameSpeedestWin::readDisconnect(MsgData& msg, ServerPlayer& player) {
    std::cout << "Remove " << m_ships.erase(&player) << " ship" << std::endl;
    for (auto& ship : m_ships) {
        std::cout << "Stay ship of " << ship.first->getId() << " " << ship.first->getName() << std::endl;
    }
    return true;
}

bool ServerGameSpeedestWin::readAction(MsgData& msg, ServerPlayer& player) {
    sf::Uint8 keysUI8;
    sf::Int32 idReq;
    msg >> keysUI8 >> idReq;
    std::bitset<4> keys = keysUI8;

    //if (!MsgData::checkValidity(sf::milliseconds(sfTime), m_lastAction[&player]))
    //  return false;
    
    doUpdate();

    Ship& ship = m_ships[&player];
    ship.setTurningNegative(keys.test(TURN_HELM_NEGATIVE));
    ship.setTurningPositive(keys.test(TURN_HELM_POSITIVE));
    ship.getSail().setTurningNegative(keys.test(TURN_SAIL_NEGATIVE));
    ship.getSail().setTurningPositive(keys.test(TURN_SAIL_POSITIVE));

    sendInfo(player, idReq);
    return true;
}
