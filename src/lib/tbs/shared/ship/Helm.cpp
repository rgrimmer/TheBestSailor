/* 
 * File:   Helm.cpp
 * Author: maxence
 * 
 * Created on 25 octobre 2014, 12:28
 */

#include "shared/ship/Helm.h"
#include <cmath>
#include <iostream>
#include <SFML/System/Vector2.hpp>

Helm::Helm(Kinematics &kinematics) :
m_kinematics(kinematics) {
}

Helm::~Helm() {
}

void Helm::turn(float angle) {
    m_kinematics.speed().x = m_kinematics.speed().x * std::cos(angle) - m_kinematics.speed().y * std::sin(angle);
    m_kinematics.speed().y = m_kinematics.speed().x * std::sin(angle)  + m_kinematics.speed().y * std::cos(angle);
//        m_kinematics.speed() += m_kinematics.speed() * sf::Vector2f(std::cos(angle),std::sin(angle)) ;
}

void Helm::update(float dt) {
    
}

void Helm::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    // Relative from ship direction
    
}

