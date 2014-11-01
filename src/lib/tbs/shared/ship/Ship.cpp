/* 
 * File:   Ship.cpp
 * Author: maxence
 * 
 * Created on 25 octobre 2014, 12:34
 */

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <math.h>

#include "shared/ship/Ship.h"

Ship::Ship() : m_helm(Helm(m_kinematics)), m_sail(Sail()) {
}

Ship::~Ship() {
}

void Ship::advance(float speed) {
    m_kinematics.speed() += sf::Vector2f(speed, speed);
}

void Ship::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    sf::CircleShape shape(10, 4);
    shape.setOutlineColor(sf::Color::Red);
    shape.rotate(45);
    shape.setOrigin(5, 5);
    target.draw(sf::CircleShape(10, 4), states);
}

void Ship::update(float dt) {
    m_kinematics.update(dt);
    setPosition(m_kinematics.position());
}