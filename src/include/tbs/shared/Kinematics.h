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
    static float degToRad(float deg);
    static float radToDeg(float rad);
    static float norme(const sf::Vector2f &vector);
    static float direction(const sf::Vector2f &vector);
    
    static sf::Vector2f vectorDir(float angle);
};

#endif	/* KINEMATICS_H */

