/* 
 * File:   Kinematics.cpp
 * Author: maxence
 * 
 * Created on 1 novembre 2014, 09:16
 */

#include <cstdlib>
#include <cmath>
#include <complex>
#include "shared/Kinematics.h"


Kinematics::Kinematics() {

}

Kinematics::~Kinematics() {

}

void Kinematics::update(float dt) {
    m_speed += m_acceleration *dt;
    m_position += m_speed * dt;
}

sf::Vector2f Kinematics::direction() const {
    float orme = norme(m_speed);
    return sf::Vector2f(m_speed.x / orme, m_speed.y/orme);
}

float Kinematics::norme(const sf::Vector2f &vector) {
    return std::sqrt(vector.x * vector.x + vector.y * vector.y);
}

sf::Vector2f Kinematics::pourcentage(const sf::Vector2f& vector) {
    float sum = std::abs(vector.x) + std::abs(vector.y);
    if(sum == 0.0f)
        return sf::Vector2f(0.5f, 0.5f);
    else
        return sf::Vector2f(vector.x / sum, vector.y / sum);
}

sf::Vector2f Kinematics::vectorDir(float angleRad) {
    // @TODO
    return sf::Vector2f(std::cos(angleRad),std::sin(angleRad));
}
