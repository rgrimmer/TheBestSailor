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

    Kinematics& kinematics() {
        return m_kinematics;
    }

    const Kinematics& kinematics() const {
        return m_kinematics;
    }
    Helm& getHelm();
    Sail& getSail();
    const Sail& getSail() const;

    void setAngle(float angle);
    float getAngle(void) const;
    
    void turnPositive(float angle = 5.0f);
    void turnNegative(float angle = 5.0f);

    void initialize(const sf::Vector2f & position, const sf::Vector2f & speed);
    void update(float dt);


private:

    Helm m_helm;
    Sail m_sail;
    Kinematics m_kinematics;
    float m_angle;

};

#endif	/* SHIP_H */

