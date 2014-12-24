/* 
 * File:   Sail.cpp
 * Author: maxence
 * 
 * Created on 25 octobre 2014, 12:37
 */

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include "shared/ship/Sail.h"

Sail::Sail() : m_line(sf::Vector2f(100.0f, 2.0f)), m_angle(0.0f), m_position() {
    m_line.setOrigin(0.0f,1.0f);
    m_line.setFillColor(sf::Color::White);
}

Sail::~Sail() {
}

void Sail::update(float dt) 
{
    //m_line.setPosition(m_position);
    //m_line.setRotation(m_angle);
}

/*virtual*/void Sail::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(m_line, states);
}

void Sail::setPosition(const sf::Vector2f & pos) {
    m_position = pos;
}

void Sail::setAngle(float angle) {
    while(angle < 0.0f)
        angle += 360.0f;
    while(angle > 360.0f)
        angle -= 360.0f;
    m_angle = angle;
}

float Sail::getAngle(void) const {
    return m_angle;
}