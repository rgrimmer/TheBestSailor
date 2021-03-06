/* 
 * File:   Input.cpp
 * Author: maxence
 * 
 * Created on 19 janvier 2015, 18:50
 */

#include "client/network/Input.h"

Input::Input() {
}

Input::Input(std::bitset<4> actions, sf::Time time)
: m_time(time)
, m_actions(actions) {
}

Input::~Input() {
}

sf::Time Input::getTime() const {
    return m_time;
}

const std::bitset<4>& Input::getActions() const {
    return m_actions;
}
