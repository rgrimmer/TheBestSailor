/* 
 * File:   RequestDisconnect.h
 * Author: maxence
 *
 * Created on 11 décembre 2014, 21:28
 */

#ifndef REQUESTDISCONNECT_H
#define	REQUESTDISCONNECT_H

#include "RequestData.h"

class RequestDisconnect : public RequestData {
public:
    RequestDisconnect();
    virtual ~RequestDisconnect();
    
    virtual reqType getType() const;

private:
    virtual void getDataFrom(sf::Packet& packet);
    virtual void putDataIn(sf::Packet& packet) const;

};

#endif	/* REQUESTDISCONNECT_H */

