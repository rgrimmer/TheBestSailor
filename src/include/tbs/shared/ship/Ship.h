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
#include "shared/Kinematics.h"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>

class Ship : public sf::Drawable, public sf::Transformable {
public:
    Ship();
    virtual ~Ship();
    
    inline Kinematics& kinematics() { return m_kinematics; }
    inline const Kinematics& kinematics() const { return m_kinematics; }
    inline Helm& helm() {return m_helm; }
    void advance(float speed);
    void update(float dt);
    
    Sail* getSail(void);
    
private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    sf::RectangleShape m_shape;
    Helm m_helm;
    Sail* m_sail;
    Kinematics m_kinematics;
};

#endif	/* SHIP_H */

