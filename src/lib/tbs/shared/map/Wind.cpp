/* 
 * File:   Wind.cpp
 * Author: maxence
 * 
 * Created on 20 novembre 2014, 17:12
 */
#include <math.h>
#include "shared/map/Wind.h"

Wind::Wind(float direction, float force) :
m_direction(direction), m_force(force)
{

}

Wind::~Wind() {
}

float& Wind::direction() {
    return m_direction;
}

float Wind::getDirection() const {
    return m_direction;
}

float& Wind::force() {
    return m_force;
}

sf::Vector2f Wind::getVector() const {
    float rad = (m_direction - 180) / 180 * M_PI;
    return sf::Vector2f(cos(rad) * m_force, sin(rad) * m_force);
}

