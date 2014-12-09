/* 
 * File:   Kinematics.cpp
 * Author: maxence
 * 
 * Created on 1 novembre 2014, 09:16
 */

#include <cstdlib>
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

float Kinematics::direction() const {
    return Kinematics::direction(m_speed);
}

// Template : in header
//float Kinematics::norme(const sf::Vector2<T> &vector);

//sf::Vector2f Kinematics::pourcentage(const sf::Vector2f& vector) {
//    float sum = std::abs(vector.x) + std::abs(vector.y);
//    if(sum == 0.0f)
//        return sf::Vector2f(0.5f, 0.5f);
//    else
//        return sf::Vector2f(vector.x / sum, vector.y / sum);
//}

sf::Vector2f Kinematics::vectorDir(float angleRad) {
    return sf::Vector2f(std::cos(angleRad),std::sin(angleRad));
}
