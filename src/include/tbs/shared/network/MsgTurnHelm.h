/* 
 * File:   MsgTurnHelm.h
 * Author: remy
 *
 * Created on 10 décembre 2014, 10:25
 */

#ifndef MSG_TURN_HELM_H
#define	MSG_TURN_HELM_H

#include <shared/network/MessageData.h>

class MsgTurnHelm : public MessageData {
public:
    explicit MsgTurnHelm(msgOrientation orientation = UNDEF);
    virtual ~MsgTurnHelm();

    msgOrientation getOrientation() const;
    virtual MsgType getType() const;

private:
    virtual void getDataFrom(sf::Packet& packet);
    virtual void putDataIn(sf::Packet& packet) const;


private:
    msgOrientation m_orientation;

};

#endif	/* MSG_TURN_HELM_H */

