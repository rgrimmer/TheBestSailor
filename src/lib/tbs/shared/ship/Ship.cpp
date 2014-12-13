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
}

Ship::~Ship() {
    delete m_sail;
}

void Ship::initialize(const sf::Vector2f & position, const sf::Vector2f & speed) {
    m_kinematics.initialize(position, speed);
}

void Ship::update(float dt) {
    m_kinematics.update(dt);
    m_sail->update(dt);
    m_helm.update(dt);
}

Sail* Ship::getSail(void) {
    return m_sail;
}