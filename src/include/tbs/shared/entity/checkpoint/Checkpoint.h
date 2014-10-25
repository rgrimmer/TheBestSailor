/* 
 * File:   Checkpoint.h
 * Author: remy
 *
 * Created on 21 octobre 2014, 13:59
 */

#pragma once

#include <SFML/System/Vector2.hpp>

class Checkpoint {
    
public:
    Checkpoint(const sf::Vector2i & pos);
    virtual ~Checkpoint();
    
private:
    sf::Vector2i m_position;
};