/* 
 * File:   World.cpp
 * Author: remy
 *
 * Created on 10 décembre 2014, 16:13
 */

#ifndef WORLD_CPP
#define	WORLD_CPP

#include <SFML/System/Vector2.hpp>

#include "client/World.h"
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

World::World() : m_map(nullptr), m_wind(nullptr), m_ship() {

}

World::~World() {

}

void World::initialize() {
    Gradient::initialize();
    m_ship.kinematics().position() = {200., 200.};
    m_ship.sail().setAngle(80.0f);
}

void World::release() {
    delete m_map;
    delete m_wind;
}

void World::initializeMap(int height, int width, double seed) {
    m_map = new HeigthMap(MapHeader(height, width, seed));
    m_wind = new WindMap(MapHeader(height, width, seed));
}

void World::update(float dt) {
    Wind wind = m_wind->wind(static_cast<sf::Vector2i> (m_ship.kinematics().position() / sf::Vector2f(TILE_SIZE, TILE_SIZE)));

    sf::Vector2f shipVector = m_ship.kinematics().speed();
    sf::Vector2f windVector = wind.getVector();

    sf::Vector2f coefSail(1.0f, 1.0f);
    sf::Vector2f coefHelm(1.0f, 1.0f);

    sf::Vector2f frottement(0.001f, 0.001f);
    sf::Vector2f apparentWind = windVector - shipVector;

    float apparentWindDir = Kinematics::direction(apparentWind);
    float sailDir = Kinematics::degToRad(m_ship.sail().getAngle());
    float helmDir = Kinematics::degToRad(m_ship.helm().angle());
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

Ship& World::getShip() {
    return m_ship;
}

HeigthMap& World::getMap() const {
    return *m_map;
}

WindMap& World::getWind() const {
    return *m_wind;
}

#endif	/* WORLD_CPP */

