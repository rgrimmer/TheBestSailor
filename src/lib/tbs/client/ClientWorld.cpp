/* 
 * File:   ClientWorld.cpp
 * Author: remy
 *
 * Created on 10 décembre 2014, 16:13
 */

#ifndef WORLD_CPP
#define	WORLD_CPP

#include <iostream>

#include <SFML/System/Vector2.hpp>

#include "client/ClientWorld.h"
#include "client/map/Gradient.h"

#include "shared/Utils.h"
#include "client/checkpoint/ClientCheckPointManager.h"

sf::Vector2f operator*(const sf::Vector2f &v1, const sf::Vector2f &v2) {
    return sf::Vector2f(v1.x * v2.x, v1.y * v2.y);
}

sf::Vector2f operator*(const sf::Vector2f &v1, float coef) {
    return sf::Vector2f(v1.x * coef, v1.y * coef);
}

sf::Vector2f operator/(const sf::Vector2f &v1, const sf::Vector2f &v2);

sf::Packet& operator>>(sf::Packet& packet, ClientWorld& world) {
    world.initialize();

    Map map;
    packet >> map;
    world.setMap(map);

    // @TODO : add ship
    return packet;
}

ClientWorld::ClientWorld()
: m_mapmap()
, m_checkPointManager() {
}

ClientWorld::~ClientWorld() {
}

void ClientWorld::initialize() {
    Gradient::initialize();
}

void ClientWorld::setMap(const Map& map) {
    m_mapmap = map;
}

void ClientWorld::initializeMap(int width, int height, int heightMapSeed, int windMapSeed) {
    m_mapmap = Map(width, height, heightMapSeed, windMapSeed);
}

void ClientWorld::update(float dt) {
    for (auto& pairShip : m_ships) {
        updateShip(pairShip.second, dt);
    }
}

void ClientWorld::updateShip(Ship& ship, float dt) {
    std::cout << "update client ship" << std::endl;
    Wind wind = m_mapmap.getWind(static_cast<sf::Vector2i> (ship.getPosition()));
    float shipDirRad = Kinematics::degToRad(ship.getAngle());
    sf::Vector2f outP(std::cos(shipDirRad), std::sin(shipDirRad));

    updateSail(ship);

    // Temporary equation 
    sf::Vector2f windForce = wind.getVector() * std::sin(Kinematics::degToRad(std::abs(ship.getSail().getAngle() - wind.getDirection())));
    sf::Vector2f velocity = std::sqrt(windForce.x * windForce.x + windForce.y * windForce.y) * outP;
    ship.setVelocity(velocity);

    if (collideWithMap(ship, ship.getVelocity())) {
        ship.setVelocity({0.0f, 0.0f});
    }

    ship.update(dt);
}

void ClientWorld::updateSail(Ship& ship) {
    Wind wind = m_mapmap.getWind(static_cast<sf::Vector2i> (ship.getPosition()));
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

bool ClientWorld::collideWithMap(const Ship & ship, const sf::Vector2f & velocity) {
    int x = (ship.getPosition().x + velocity.x);
    int y = (ship.getPosition().y + velocity.y);
    return !WATER(m_mapmap.getHeightMap().getValue(x, y));
}

bool ClientWorld::windComeFromFront(const Ship& ship, const Wind& wind) const {
    return (static_cast<int> (450 - ship.getAngle() + wind.getDirection()) % 360 > 180);
}

bool ClientWorld::windComeFromTribord(const Ship& ship, const Wind& wind) const {
    return (static_cast<int> (360 - ship.getAngle() + wind.getDirection()) % 360 > 180);
}

void ClientWorld::addCheckPoint(sf::Vector2i position) {
    m_checkPointManager.addCheckPoint(position);
}

const ClientCheckPointManager& ClientWorld::getCheckPointManager() const {
    return m_checkPointManager;
}

ClientCheckPointManager& ClientWorld::getCheckPointManager() {
    return m_checkPointManager;
}

std::map<unsigned int, Ship>& ClientWorld::getShips() {
    return m_ships;
}

const std::map<unsigned int, Ship>& ClientWorld::getShips() const {
    return m_ships;
}

Ship& ClientWorld::getClientShip() {
    return *m_ship;
}

const Ship& ClientWorld::getClientShip() const {
    return *m_ship;
}

void ClientWorld::setClientShip(Ship* ship) {
    m_ship = ship;
}

Map& ClientWorld::getMap() {
    return m_mapmap;
}

const Map& ClientWorld::getMap() const {
    return m_mapmap;
}

HeigthMap& ClientWorld::getHeightMap() {
    return m_mapmap.getHeightMap();
}

const HeigthMap& ClientWorld::getHeightMap() const {
    return m_mapmap.getHeightMap();
}

WindMap& ClientWorld::getWindMap() {
    return m_mapmap.getWindMap();
}

const WindMap& ClientWorld::getWindMap() const {
    return m_mapmap.getWindMap();
}

#endif	/* WORLD_CPP */

