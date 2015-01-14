/* 
 * File:   ServerCheckpoint.h
 * Author: remy
 *
 * Created on 21 octobre 2014, 13:59
 */

#pragma once

#include <SFML/System/Vector2.hpp>

class ServerCheckpoint {
    
public:
 
    ServerCheckpoint(const sf::Vector2i & pos);
    virtual ~ServerCheckpoint();
    
    sf::Vector2i getPosition() const;
    
private:
    sf::Vector2i m_position;
};