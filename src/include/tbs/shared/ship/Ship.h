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

class Ship {
public:
    Ship();
    virtual ~Ship();
    
    void initialize(const sf::Vector2f & position, const sf::Vector2f & speed);
    
    inline Kinematics& kinematics() { return m_kinematics; }
    inline const Kinematics& kinematics() const { return m_kinematics; }
    inline Helm& helm() {return m_helm; }
    inline Sail& sail() { return *m_sail; }
    inline const Sail& sail() const { return *m_sail; }
    void update(float dt);
   
    void setAngle(float angle);
    
    Sail* getSail(void);
    float getAngle(void) const;
    
private:

    Helm m_helm;
    Sail* m_sail;
    Kinematics m_kinematics;
    float m_angle;
    
};

#endif	/* SHIP_H */

