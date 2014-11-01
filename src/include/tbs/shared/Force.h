/* 
 * File:   Force.h
 * Author: maxence
 *
 * Created on 1 novembre 2014, 16:58
 */

#ifndef FORCE_H
#define	FORCE_H

#include <string>
#include <SFML/System/Vector2.hpp>

class Force {
public:
    Force();
    virtual ~Force();
    
    inline float& angle() { return m_angle; }
    inline float& norm() { return m_norm; }
    inline sf::Vector2f point() { return m_applicationPoint; }
    
    std::string toString() const;
private:
    float m_angle;
    float m_norm;
    sf::Vector2f m_applicationPoint;

};

#endif	/* FORCE_H */

