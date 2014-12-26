/* 
 * File:   ClientWorld.cpp
 * Author: remy
 *
 * Created on 10 décembre 2014, 16:13
 */

#ifndef WORLD_CPP
#define	WORLD_CPP

#include <SFML/System/Vector2.hpp>

#include "client/ClientWorld.h"
#include "client/map/Gradient.h"

#include "shared/Utils.h"

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

ClientWorld::ClientWorld() : m_mapmap() {

}

ClientWorld::~ClientWorld() {
}

void ClientWorld::initialize() {
    Gradient::initialize();
    m_ship.initialize(sf::Vector2f(1000.0f, 1000.0f), sf::Vector2f(0.0f, 0.0f));
}

void ClientWorld::setMap(const Map& map) {
    m_mapmap = map;
}

void ClientWorld::initializeMap(int width, int height, int heightMapSeed, int windMapSeed) {
    m_mapmap = Map(width, height, heightMapSeed, windMapSeed);
}

void ClientWorld::update(float dt) {
    m_ship.update(dt);
}

Ship& ClientWorld::getShip() {
    return m_ship;
}

const Ship& ClientWorld::getShip() const {
    return m_ship;
}

bool ClientWorld::windComeFromFront(const Wind &wind) const {
    return (static_cast<int> (450 - m_ship.getAngle() + wind.getDirection()) % 360 > 180);
}

bool ClientWorld::windComeFromTribord(const Wind &wind) const {
    return (static_cast<int> (360 - m_ship.getAngle() + wind.getDirection()) % 360 > 180);
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

