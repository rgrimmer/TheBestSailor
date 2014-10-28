/* 
 * File:   Player.cpp
 * Author: maxence
 * 
 * Created on 20 octobre 2014, 18:28
 */

#include "shared/Player.h"

Player::Player(const std::string& name, SocketQueuBuffer *buffer) : m_name(name), m_buffer(buffer) {
}

Player::Player(const Player& orig) {
}

Player::~Player() {
}

const std::string& Player::getName() const {
    return m_name;
}