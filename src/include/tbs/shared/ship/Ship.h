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

class Ship {
public:
    Ship();
    virtual ~Ship();
private:
    Helm m_helm;
    Sail m_sail;

};

#endif	/* SHIP_H */

