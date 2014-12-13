/* 
 * File:   Kinematics.cpp
 * Author: maxence
 * 
 * Created on 1 novembre 2014, 09:16
 */

#include <cstdlib>
#include <complex>
#include "shared/Kinematics.h"

#include <iostream>

Kinematics::Kinematics() {

}

Kinematics::~Kinematics() {

}

void Kinematics::initialize(const sf::Vector2f & position, const sf::Vector2f & speed) {
    m_position = position;
    m_speed = speed;
}

void Kinematics::update(float dt) {
    m_speed += m_acceleration *dt;
    m_position += m_speed * dt;
}

float Kinematics::direction() const {
    return Kinematics::direction(m_speed);
}

float Kinematics::degToRad(float deg) {
    return deg / 180.0 * M_PI;
}

float Kinematics::radToDeg(float rad) {
    return rad * 180.0 / M_PI;
}

float Kinematics::norme(const sf::Vector2f &vector) {
    return std::sqrt(vector.x * vector.x + vector.y * vector.y);
}

float Kinematics::direction(const sf::Vector2f &vector) {
    float angleInRad = std::atan2(vector.y, vector.x);
    return Kinematics::radToDeg(angleInRad);
}

sf::Vector2f Kinematics::vectorDir(float angleRad) {
    return sf::Vector2f(std::cos(angleRad), std::sin(angleRad));
}
