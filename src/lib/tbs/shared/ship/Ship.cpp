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

Ship::Ship() {
    m_sail = new Sail();
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

void Ship::setAngle(float angle) {
    m_angle = angle;
}

Sail* Ship::getSail(void) {
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
