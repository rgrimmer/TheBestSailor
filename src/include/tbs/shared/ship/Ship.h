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
    Ship(int type = 0);
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
    
    int getType() const;
    
    void turnPositive(float angle);
    void turnNegative(float angle);
    bool isTurningPositive() const;
    bool isTurningNegative() const;
    void setTurningPositive(bool value);
    void setTurningNegative(bool value);

    void initialize(const sf::Vector2f & position, const sf::Vector2f & speed);
    void update(float dt);


private:
    bool m_turnPositive;
    bool m_turnNegative;
    Helm m_helm;
    Sail m_sail;
    Kinematics m_kinematics;
    float m_angle;
    int m_type;

};

#endif	/* SHIP_H */

