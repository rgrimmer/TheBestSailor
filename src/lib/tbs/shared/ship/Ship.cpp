/* 
 * File:   Ship.cpp
 * Author: maxence
 * 
 * Created on 25 octobre 2014, 12:34
 */

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <math.h>


#include "shared/ship/Ship.h"

Ship::Ship() : m_shape(sf::Vector2f(50.0f, 100.0f)), m_helm(Helm(m_kinematics)) {
    m_shape.setOrigin(25, 50);
    m_shape.setFillColor(sf::Color::Red);
    
    m_sail = new Sail();
}

Ship::~Ship() {
    
    delete m_sail;
}

void Ship::advance(float speed) {
    m_kinematics.speed() += sf::Vector2f(speed, speed);
}


void Ship::update(float dt) {
    setPosition(m_kinematics.position());
    m_sail->setPosition(m_kinematics.position());

    m_kinematics.update(dt);
    m_sail->update(dt);
}


void Ship::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();

    target.draw(m_shape, states);
    target.draw(*m_sail);
}

Sail* Ship::getSail(void) {
    return m_sail;
}