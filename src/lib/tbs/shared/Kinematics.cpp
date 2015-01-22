/* 
 * File:   Kinematics.cpp
 * Author: maxence
 * 
 * Created on 1 novembre 2014, 09:16
 */

#include <cstdlib>
#include <complex>
#include <cmath>

#include "shared/Kinematics.h"

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
