/* 
 * File:   Helm.h
 * Author: maxence
 *
 * Created on 25 octobre 2014, 12:28
 */

#ifndef HELM_H
#define	HELM_H

#include "shared/Kinematics.h"

class Helm {
public:
    Helm(Kinematics &kinematics);
    virtual ~Helm();
    
    inline float& angle() { return m_angle; }
    inline float angle() const { return m_angle; }
    void turn(float angle);
    
    
private:
    float m_angle;
    Kinematics &m_kinematics;

};

#endif	/* HELM_H */

