/* 
 * File:   Ship.h
 * Author: maxence
 *
 * Created on 25 octobre 2014, 12:34
 */

#ifndef SHIP_H
#define	SHIP_H

#include "Helm.h"
#include "Sail.h"

#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>

class Ship : public sf::Drawable, public sf::Transformable {
public:
    Ship();
    virtual ~Ship();
    
    void turnLeft(float angle);
    void turnRight(float angle);
    void advance(float distance);
    
private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    Helm m_helm;
    Sail m_sail;

};

#endif	/* SHIP_H */

