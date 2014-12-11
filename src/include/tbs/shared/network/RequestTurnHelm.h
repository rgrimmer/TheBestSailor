/* 
 * File:   RequestTurnHelm.h
 * Author: remy
 *
 * Created on 10 décembre 2014, 10:25
 */

#ifndef REQUEST_TURN_HELM_H
#define	REQUEST_TURN_HELM_H

#include <shared/network/RequestData.h>

class RequestTurnHelm : public RequestData {
public:
    explicit RequestTurnHelm(reqOrientation orientation = UNDEF);
    virtual ~RequestTurnHelm();

    reqOrientation getOrientation() const;
    virtual reqType getType() const;

private:
    virtual void getDataFrom(sf::Packet& packet);
    virtual void putDataIn(sf::Packet& packet) const;


private:
    reqOrientation m_orientation;

};

#endif	/* REQUEST_TURN_HELM_H */

