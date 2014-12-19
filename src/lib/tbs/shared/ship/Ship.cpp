/* 
 * File:   Ship.cpp
 * Author: maxence
 * 
 * Created on 25 octobre 2014, 12:34
 */

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <math.h>


#include "shared/ship/Ship.h"
#include "shared/Font.h"

Ship::Ship() {
}

Ship::~Ship() {
}

void Ship::update(float dt) {
//    m_sail->setPosition(m_kinematics.position());

    m_kinematics.update(dt);
    m_sail.update(dt);
    m_helm.update(dt);
}

const Sail& Ship::getSail() const {
    return m_sail;
}

Sail& Ship::getSail() {
    return m_sail;
}

Helm& Ship::getHelm() {
    return m_helm;
}
