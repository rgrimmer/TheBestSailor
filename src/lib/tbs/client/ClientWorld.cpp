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

ClientWorld::ClientWorld() : m_mapmap(){

}

ClientWorld::~ClientWorld() {
}

void ClientWorld::initialize() {
    Gradient::initialize();
    m_ship.kinematics().position() = {200., 200.};
    m_ship.getSail().setAngle(80.0f);
}

void ClientWorld::setMap(const Map& map) {
    m_mapmap = map;
}

void ClientWorld::initializeMap(int width, int height, int heightMapSeed, int windMapSeed) {
    m_mapmap = Map(width, height, heightMapSeed, windMapSeed);
}

void ClientWorld::update(float dt) {
    Wind wind = m_mapmap.getWindMap().wind(static_cast<sf::Vector2i> (m_ship.kinematics().position() / sf::Vector2f(TILE_SIZE, TILE_SIZE)));

    sf::Vector2f shipVector = m_ship.kinematics().speed();
    sf::Vector2f windVector = wind.getVector();

    sf::Vector2f coefSail(1.0f, 1.0f);
    sf::Vector2f coefHelm(1.0f, 1.0f);

    sf::Vector2f frottement(0.001f, 0.001f);
    sf::Vector2f apparentWind = windVector - shipVector;

    float apparentWindDir = Kinematics::direction(apparentWind);
    float sailDir = Kinematics::degToRad(m_ship.getSail().getAngle());
    float helmDir = Kinematics::degToRad(m_ship.getHelm().angle());
    float shipDir = Kinematics::degToRad(Kinematics::direction(m_ship.kinematics().speed()));
    if (isnan(shipDir))
        shipDir = 0;

    float angleAlpha = 0.0f; // @TODO angle ventApparent - voile
    //        float angleAlpha = 
    float angleBeta = shipDir - sailDir; // @TODO angle axe du bateau - voile 

    // Equation from https://www.ensta-bretagne.fr/jaulin/jaulincifa2004.pdf

    sf::Vector2f sailVector =
            coefSail * (
            windVector * std::cos(shipDir + angleBeta)
            - shipVector * std::sin(shipDir)
            );

    sf::Vector2f helmVector = coefHelm * shipVector * std::sin(helmDir);

    sf::Vector2f forceDePousser1 =
            (sailVector * std::sin(angleBeta)
            - helmVector * std::sin(helmDir)
            - shipVector * frottement)
            / 1.0f; // Masse

    // Equation from wikipedia
    sf::Vector2f CONSTANTE(0.1f, 0.1f);
    float sinAB = std::sin(angleAlpha + angleBeta);
    sf::Vector2f forceDePousser2 = CONSTANTE * sinAB * angleAlpha - helmVector * std::sin(helmDir);

    sf::Vector2f forceDePousser = forceDePousser1;

    m_ship.kinematics().speed() = windVector /* Kinematics::vectorDir(degToRad(angleDirShip))*/;

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

