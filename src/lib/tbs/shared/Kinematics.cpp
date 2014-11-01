/* 
 * File:   Kinematics.cpp
 * Author: maxence
 * 
 * Created on 1 novembre 2014, 09:16
 */

#include "shared/Kinematics.h"

Kinematics::Kinematics() {

}

Kinematics::~Kinematics() {

}

void Kinematics::update(float dt) {
    m_speed += m_acceleration *dt;
    m_position += m_speed * dt;
}