/* 
 * File:   Kinematics.h
 * Author: maxence
 *
 * Created on 1 novembre 2014, 09:16
 */

#ifndef KINEMATICS_H
#define	KINEMATICS_H

#include <SFML/System/Vector2.hpp>

class Kinematics {
public:
    Kinematics();
    virtual ~Kinematics();
    
    inline sf::Vector2f& acceleration(void) { return m_acceleration; }
    inline const sf::Vector2f& acceleration(void) const { return m_acceleration; }
    inline sf::Vector2f& speed(void) { return m_speed; }
    inline const sf::Vector2f& speed(void) const { return m_speed; }
    inline  sf::Vector2f& position(void) { return m_position; }
    inline const sf::Vector2f& position(void) const { return m_position; }
    
    void update(float dt);

private:
    sf::Vector2f m_acceleration;
    sf::Vector2f m_speed;
    sf::Vector2f m_position;

};

#endif	/* KINEMATICS_H */

