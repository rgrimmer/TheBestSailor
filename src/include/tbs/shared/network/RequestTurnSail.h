/* 
 * File:   RequestTurnHelm.h
 * Author: remy
 *
 * Created on 10 décembre 2014, 10:25
 */

#ifndef REQUEST_TURN_SAIL_H
#define	REQUEST_TURN_SAIL_H

#include <shared/network/Request.h>

class RequestTurnSail : public Request {
    
public:
    explicit RequestTurnSail(reqType type, unsigned int id);
    virtual ~RequestTurnSail();
    
    virtual sf::Packet createPacket(); 
private:

};

#endif	/* REQUEST_TURN_HELM_H */

