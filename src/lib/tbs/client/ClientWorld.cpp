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

sf::Vector2f operator/(const sf::Vector2f &v1, const sf::Vector2f &v2) {
    return sf::Vector2f(v1.x / v2.x, v1.y / v2.y);
}

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
    Wind wind = m_mapmap.getWind(static_cast<sf::Vector2i> (m_ship.kinematics().position() / sf::Vector2f(TILE_SIZE, TILE_SIZE)));

    sf::Vector2f shipVector = m_ship.kinematics().speed();
    sf::Vector2f windVector = wind.getVector();

    sf::Vector2f apparentWind = windVector - shipVector;

    float windAngle = Kinematics::direction(windVector);
    float apparentWindAngle = Kinematics::direction(apparentWind);
    float sailAngle = m_ship.getSail().getAngle();

    std::cout << "angle : " << std::abs(windAngle - sailAngle) << std::endl;
    float angleToRad = Kinematics::degToRad(std::abs(windAngle - sailAngle));

    //sf::Vector2f F = 0.1f * apparentWind * apparentWind * std::sin(Kinematics::degToRad(sailAngle));
    sf::Vector2f P = { std::cos(Kinematics::degToRad(m_ship.getAngle())), std::sin(Kinematics::degToRad(m_ship.getAngle())) };
    sf::Vector2f F = 0.1f * apparentWind * apparentWind * std::sin(angleToRad);

    sf::Vector2f Fm = (F.x * P.x + F.y * P.y) * P;
    //sf::Vector2f F = 10.0f * windVector * std::sin(angleToRad) * std::sin(angleToRad);

    // somme des forces = ma
    // v = a*t + v0
    // x = (1/2) * a.x * t * t + v0.x * t + x0
    // y = (1/2) * a.y * t * t + v0.y * t + y0

    //m_ship.kinematics().speed() = windVector /* Kinematics::vectorDir(degToRad(angleDirShip))*/;
    m_ship.kinematics().speed() = Fm;

    m_ship.update(dt);
 }

Ship& ClientWorld::getShip() {
    return m_ship;
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

