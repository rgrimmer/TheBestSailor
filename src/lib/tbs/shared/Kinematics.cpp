/* 
 * File:   Kinematics.cpp
 * Author: maxence
 * 
 * Created on 1 novembre 2014, 09:16
 */

#include <cstdlib>
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
    float absX = abs(m_speed.x);
    float absY = abs(m_speed.y);
    if(absX>absY) {
        return sf::Vector2f(m_speed.x/absX, m_speed.y/absX);
    }
    else {
        return sf::Vector2f(m_speed.x/absY, m_speed.y/absY);
    }
}
