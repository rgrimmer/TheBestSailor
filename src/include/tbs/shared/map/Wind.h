/* 
 * File:   Wind.h
 * Author: maxence
 *
 * Created on 20 novembre 2014, 17:12
 */

#ifndef WIND_H
#define	WIND_H

#include <SFML/System/Vector2.hpp>

class Wind {
public:
    Wind(float direction = 0, float force = 0);
    virtual ~Wind();
    
    float& direction();
    float& force();
    sf::Vector2f getVector() const;
private:
    float m_direction;
    float m_force;

};

#endif	/* WIND_H */

