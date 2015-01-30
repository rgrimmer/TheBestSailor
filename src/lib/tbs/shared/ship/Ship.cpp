/* 
 * File:   Ship.cpp
 * Author: maxence
 * 
 * Created on 25 octobre 2014, 12:34
 */

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <math.h>


#include "shared/ship/Ship.h"
#include "shared/Font.h"

const int Ship::maxType = 4;
const int Ship::TurnVelocity = 45;

Ship::Ship(const sf::Vector2f& position, float shipAngle, float sailAngle, int type)
: m_turnPositive(false)
, m_turnNegative(false)
, m_angle(shipAngle)
, m_type(type)
, m_position(position)
, m_velocity()
, m_acceleration()
, m_sail(sailAngle) {
}

Ship::~Ship() {
}

void Ship::initialize(const sf::Vector2f & position, const sf::Vector2f & speed) {
    m_position = position;
    m_velocity = speed;
}

void Ship::update(float dt) {
    // Update ship
    if (m_turnNegative) {
        turnNegative( dt);
    }
    if (m_turnPositive) {
        turnPositive(dt);
    }
    
    // Sail
    m_sail.update(dt);
    
    // Ship
    m_velocity += m_acceleration *dt;
    m_position += m_velocity * dt;
}

void Ship::turnNegative(float dt) {
    setAngle(m_angle - Ship::TurnVelocity * dt);
    getSail().turnNegative(dt);
}

void Ship::turnPositive(float dt) {
    setAngle(m_angle + Ship::TurnVelocity * dt);
    getSail().turnPositive(dt);
}

bool Ship::isTurningPositive() const {
    return m_turnPositive;
}

bool Ship::isTurningNegative() const {
    return m_turnNegative;
}

void Ship::setTurningPositive(bool value) {
    m_turnPositive = value;
}

void Ship::setTurningNegative(bool value) {
    m_turnNegative = value;
}

void Ship::setAngle(float angle) {
    while (angle < 0)
        angle += 360.0f;
    while (angle >= 360.0f)
        angle -= 360.0f;
    m_angle = angle;
}

const Sail& Ship::getSail() const {
    return m_sail;
}

Sail& Ship::getSail() {
    return m_sail;
}

float Ship::getAngle(void) const {
    return m_angle;
}

int Ship::getType() const {
    return m_type;
}

float Ship::getDirection() const {
    return Kinematics::direction(m_velocity);
}

sf::Vector2f& Ship::position() {
    return m_position;
}

const sf::Vector2f& Ship::getPosition() const {
    return m_position;
}

sf::Vector2f& Ship::velocity() {
    return m_velocity;
}

const sf::Vector2f& Ship::getVelocity() const {
    return m_velocity;
}

void Ship::setPosition(const sf::Vector2f& position) {
    m_position = position;
}

void Ship::setVelocity(const sf::Vector2f& velocity) {
    m_velocity = velocity;
}
