/* 
 * File:   MsgTurnHelm.h
 * Author: remy
 *
 * Created on 10 décembre 2014, 10:25
 */

#ifndef MSG_TURN_HELM_H
#define	MSG_TURN_HELM_H

#include <shared/network/MsgData.h>

class MsgTurnHelm : public MsgData {
public:
    explicit MsgTurnHelm(MsgOrientation orientation = MsgOrientation::UNDEF);
    virtual ~MsgTurnHelm();
};

#endif	/* MSG_TURN_HELM_H */

