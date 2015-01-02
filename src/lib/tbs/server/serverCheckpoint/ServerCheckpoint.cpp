/* 
 * File:   Checkpoint.h
 * Author: remy
 *
 * Created on 21 octobre 2014, 13:59
 */

#include "server/serverCheckpoint/ServerCheckpoint.h"

ServerCheckpoint::ServerCheckpoint(const sf::Vector2i & pos)
: m_position(pos) {

}

ServerCheckpoint::~ServerCheckpoint() {

}

sf::Vector2i ServerCheckpoint::getPosition() const {
    return m_position;
}
