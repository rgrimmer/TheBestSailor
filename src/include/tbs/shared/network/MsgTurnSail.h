/* 
 * File:   MsgTurnHelm.h
 * Author: remy
 *
 * Created on 10 décembre 2014, 10:25
 */

#ifndef MSG_TURN_SAIL_H
#define	MSG_TURN_SAIL_H

#include "shared/network/MsgData.h"
#include "shared/network/MsgType.h"

class MsgTurnSail : public MsgData {
public:
    explicit MsgTurnSail(MsgOrientation orientation = MsgOrientation::UNDEF);
    virtual ~MsgTurnSail();
};

#endif	/* MSG_TURN_HELM_H */

