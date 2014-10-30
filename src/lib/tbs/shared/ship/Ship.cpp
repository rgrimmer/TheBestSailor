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

Ship::Ship() : m_helm(Helm()), m_sail(Sail()) {
}

Ship::~Ship() {
}

void Ship::turnLeft(float angle) {
    rotate(-angle);
}

void Ship::turnRight(float angle) {
    
    rotate(angle);
}

void Ship::advance(float distance) {
    move(distance*cos(getRotation()),distance*sin(getRotation()));
}


void Ship::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    sf::CircleShape shape(10, 4);
    shape.setFillColor(sf::Color(150 ,75 , 0));
    shape.rotate(45);
    shape.setOrigin(5,5);
    target.draw(sf::CircleShape(10, 4), states);
}
