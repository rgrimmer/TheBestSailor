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
    
    Kinematics& kinematics() { return m_kinematics; }
    const Kinematics& kinematics() const { return m_kinematics; }
    Helm& getHelm();
    Sail& getSail();
    const Sail& getSail() const;
    void update(float dt);
    
private:

    Helm m_helm;
    Sail m_sail;
    Kinematics m_kinematics;
    
};

#endif	/* SHIP_H */

