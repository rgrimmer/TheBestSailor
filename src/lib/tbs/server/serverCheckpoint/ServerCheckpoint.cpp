/* 
 * File:   Checkpoint.h
 * Author: remy
 *
 * Created on 21 octobre 2014, 13:59
 */

#include "server/serverCheckpoint/ServerCheckpoint.h"

ServerCheckpoint::ServerCheckpoint(const sf::Vector2i & pos)
: m_position(pos)
, m_eState(e_state_off)
{

}

ServerCheckpoint::~ServerCheckpoint() {

}

void ServerCheckpoint::activate() {
    m_eState = e_state_on;
}

void ServerCheckpoint::deactivate() {
    m_eState = e_state_off;
}

bool ServerCheckpoint::isActivated() const{
    return m_eState == e_state_on;
}

sf::Vector2i ServerCheckpoint::getPosition() const {
    return m_position;
}
