/* 
 * File:   Sail.cpp
 * Author: maxence
 * 
 * Created on 25 octobre 2014, 12:37
 */

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include "shared/ship/Sail.h"

Sail::Sail() 
: m_angle(0.0f) {
}

Sail::~Sail() {
}

void Sail::update(float dt) {
}

void Sail::turnNegative(float angle) {
    setAngle(m_angle - angle);
}

void Sail::turnPositive(float angle) {
    setAngle(m_angle + angle);
}

bool Sail::isTurningPositive() const {
    return m_turnPositive;
}

bool Sail::isTurningNegative() const {
    return m_turnNegative;
}

void Sail::setTurningPositive(bool value) {
    m_turnPositive = value;
}

void Sail::setTurningNegative(bool value) {
    m_turnNegative = value;
}

void Sail::setAngle(float angle) {
    while (angle < 0.0f)
        angle += 360.0f;
    while (angle > 360.0f)
        angle -= 360.0f;
    m_angle = angle;
}

float Sail::getAngle(void) const {
    return m_angle;
}