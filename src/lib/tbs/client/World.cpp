/* 
 * File:   World.cpp
 * Author: remy
 *
 * Created on 10 décembre 2014, 16:13
 */

#ifndef WORLD_CPP
#define	WORLD_CPP

#include <iostream>

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
    m_ship.initialize(sf::Vector2f(1000.0f, 1000.0f), sf::Vector2f(0.0f, 0.0f));
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
    
    sf::Vector2f apparentWind = windVector - shipVector;
    
    float windAngle = Kinematics::direction(windVector);
    float apparentWindAngle = Kinematics::direction(apparentWind);
    float sailAngle = m_ship.sail().getAngle();
    
    std::cout << "angle : " << std::abs(windAngle - sailAngle) << std::endl;
    float angleToRad = Kinematics::degToRad(std::abs(windAngle - sailAngle));
    
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

