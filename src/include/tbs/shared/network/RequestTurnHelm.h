/* 
 * File:   RequestTurnHelm.h
 * Author: remy
 *
 * Created on 10 décembre 2014, 10:25
 */

#ifndef REQUEST_TURN_HELM_H
#define	REQUEST_TURN_HELM_H

#include <shared/network/Request.h>

class RequestTurnHelm : public Request {
    
public:
    explicit RequestTurnHelm(reqType type, unsigned int id);
    virtual ~RequestTurnHelm();
    
    virtual sf::Packet createPacket(); 
private:

};

#endif	/* REQUEST_TURN_HELM_H */

