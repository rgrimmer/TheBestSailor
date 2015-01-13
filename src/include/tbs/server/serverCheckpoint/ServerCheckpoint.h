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
    enum EState {
        e_state_on,
        e_state_off
    };
 
    ServerCheckpoint(const sf::Vector2i & pos);
    virtual ~ServerCheckpoint();
    
    void activate();
    void deactivate();
    
    bool isActivated() const;
    sf::Vector2i getPosition() const;
    
private:
    sf::Vector2i m_position;
    EState m_eState;
};