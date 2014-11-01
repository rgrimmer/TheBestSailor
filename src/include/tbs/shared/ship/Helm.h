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
    
    void turn(float angle);
    
    
private:
    Kinematics &m_kinematics;

};

#endif	/* HELM_H */

