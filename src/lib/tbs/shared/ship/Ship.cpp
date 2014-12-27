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

Ship::Ship()
: m_turnPositive(false)
, m_turnNegative(false) {
    m_angle = 45.0f;
}

Ship::~Ship() {
}

void Ship::initialize(const sf::Vector2f & position, const sf::Vector2f & speed) {
    m_kinematics.initialize(position, speed);
}

void Ship::update(float dt) {
    m_kinematics.update(dt);
    m_sail.update(dt);
    m_helm.update(dt);
}

void Ship::turnNegative(float angle) {
    setAngle(m_angle - angle);
}

void Ship::turnPositive(float angle) {
    setAngle(m_angle + angle);
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

Helm& Ship::getHelm() {
    return m_helm;
}

float Ship::getAngle(void) const {
    return m_angle;
}
