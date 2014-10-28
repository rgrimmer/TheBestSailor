/* 
 * File:   Wind.cpp
 * Author: maxence
 * 
 * Created on 28 octobre 2014, 23:06
 */

#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics.hpp>

#include "shared/map/Wind.h"

Wind::Wind() {
}

Wind::Wind(int strength, float direction) :
m_strength(strength),
m_direction(direction)
{
    setRotation(direction);
}

Wind::Wind(const Wind& orig) {
}

Wind::~Wind() {
}

void Wind::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    sf::CircleShape triangle(10,3);
    states.transform *= getTransform();
    target.draw(triangle, states);
}


