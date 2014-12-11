/* 
 * File:   RequestTurnHelm.h
 * Author: remy
 *
 * Created on 10 décembre 2014, 10:25
 */

#ifndef REQUEST_TURN_SAIL_H
#define	REQUEST_TURN_SAIL_H

#include <shared/network/RequestData.h>

class RequestTurnSail : public RequestData {
public:
    explicit RequestTurnSail(reqOrientation orientation = UNDEF);
    virtual ~RequestTurnSail();

    reqOrientation getOrientation() const;
    virtual reqType getType() const;

    virtual void getDataFrom(sf::Packet& packet);
    virtual void putDataIn(sf::Packet& packet) const;

private:
    reqOrientation m_orientation;
};

#endif	/* REQUEST_TURN_HELM_H */

