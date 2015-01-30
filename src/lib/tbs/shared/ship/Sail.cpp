/* 
 * File:   Sail.cpp
 * Author: maxence
 * 
 * Created on 25 octobre 2014, 12:37
 */

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include "shared/ship/Sail.h"

const int Sail::TurnVelocity = 45;

Sail::Sail(float angle)
: m_angle(angle)
, m_turnNegative(false)
, m_turnPositive(false) {
}

Sail::~Sail() {
}

void Sail::update(float dt) {
    if (m_turnNegative) {
        turnNegative(dt);
    }
    if (m_turnPositive) {
        turnPositive(dt);
    }
}

void Sail::turnNegative(float dt) {
    setAngle(m_angle - dt * Sail::TurnVelocity);
}

void Sail::turnPositive(float dt) {
    setAngle(m_angle + dt * Sail::TurnVelocity);
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