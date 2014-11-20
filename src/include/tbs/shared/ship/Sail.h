/* 
 * File:   Sail.h
 * Author: maxence
 *
 * Created on 25 octobre 2014, 12:37
 */

#ifndef SAIL_H
#define	SAIL_H

#include <SFML/System/Vector2.hpp>

class Sail {
public:
    Sail();
    virtual ~Sail();
    float getAngleWith(const sf::Vector2f &direction) { return 10; }
private:

};

#endif	/* SAIL_H */

