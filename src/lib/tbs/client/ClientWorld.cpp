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
    Wind wind = m_mapmap.getWind(static_cast<sf::Vector2i> (m_ship.kinematics().position() / sf::Vector2f(TILE_SIZE, TILE_SIZE)));

    sf::Vector2f shipVector = m_ship.kinematics().speed();
    sf::Vector2f windVector = wind.getVector();

    sf::Vector2f apparentWind = windVector - shipVector;


    float windAngle = Kinematics::direction(windVector);
    float apparentWindAngle = Kinematics::direction(apparentWind);
    float sailAngle = m_ship.getSail().getAngle();

    //    std::cout << "angle : " << std::abs(apparentWindAngle - sailAngle) << std::endl;
    float angleToRad = Kinematics::degToRad(std::abs(windAngle - sailAngle));

    //sf::Vector2f F = 0.1f * apparentWind * apparentWind * std::sin(Kinematics::degToRad(sailAngle));
    sf::Vector2f P(std::cos(Kinematics::degToRad(m_ship.getAngle())), std::sin(Kinematics::degToRad(m_ship.getAngle())));
    sf::Vector2f F = apparentWind * apparentWind * std::sin(apparentWindAngle);

    //sf::Vector2f F = 10.0f * windVector * std::sin(angleToRad) * std::sin(angleToRad);

    // somme des forces = ma
    // v = a*t + v0
    // x = (1/2) * a.x * t * t + v0.x * t + x0
    // y = (1/2) * a.y * t * t + v0.y * t + y0

    //m_ship.kinematics().speed() = windVector /* Kinematics::vectorDir(degToRad(angleDirShip))*/;
    m_ship.kinematics().speed() = getShipVelocity();

    m_ship.update(dt);
}

sf::Vector2f ClientWorld::getShipVelocity() const {
    sf::Vector2f A, B, C, D, E;
    return getShipVelocity(A, B, C, D, E);
}

sf::Vector2f ClientWorld::getShipVelocity(sf::Vector2f& outWindVector, sf::Vector2f& outApparantWind, sf::Vector2f& outP, sf::Vector2f& outF, sf::Vector2f& outFM) const {
    Wind wind = m_mapmap.getWind(static_cast<sf::Vector2i> (m_ship.kinematics().position() / sf::Vector2f(TILE_SIZE, TILE_SIZE)));
    float alphaRad, apDir;
    outWindVector = wind.getVector();
    outApparantWind = outWindVector - m_ship.kinematics().speed();
    outP = sf::Vector2f(std::cos(Kinematics::degToRad(m_ship.getAngle())), std::sin(Kinematics::degToRad(m_ship.getAngle())));
    apDir = Kinematics::direction(outApparantWind);
//    alphaRad = Kinematics::degToRad(std::abs(apDir - m_ship.getSail().getAngle()));
    alphaRad = Kinematics::degToRad(m_ship.getAngle());
    outF = 0.1f * outApparantWind * outApparantWind * std::sin(alphaRad);
//    outFM = std::sqrt(outF.x * outF.x + outF.y * outF.y) * outP - (m_ship.kinematics().speed() * 0.1f);
    outFM = (outF.x * outP.x + outF.y * outP.y) * outP;
    return outFM;
}

Ship& ClientWorld::getShip() {
    return m_ship;
}

const Ship& ClientWorld::getShip() const {
    return m_ship;
}

bool ClientWorld::windComeFromFront(const Wind &wind) const {
    return (static_cast<int> (450 - m_ship.getAngle() + wind.getDirection()) % 360 < 180);
}

bool ClientWorld::windComeFromTribord(const Wind &wind) const {
    return (static_cast<int> (360 - m_ship.getAngle() + wind.getDirection()) % 360 < 180);
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

