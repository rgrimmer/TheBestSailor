/* 
 * File:   Force.cpp
 * Author: maxence
 * 
 * Created on 1 novembre 2014, 16:58
 */

#include "shared/Force.h"

Force::Force() : m_angle(0), m_norm(0), m_applicationPoint() {
}

Force::~Force() {
}

std::string Force::toString() const {
    return "norm : " + std::to_string(m_norm) + 
            "; angle : " + std::to_string(m_angle) + 
            "; point : " + std::to_string(m_applicationPoint.x) + std::to_string(m_applicationPoint.y);
}


