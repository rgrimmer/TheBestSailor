/* 
 * File:   MsgAction.h
 * Author: remy
 *
 * Created on 26 décembre 2014, 13:51
 */

#ifndef MSGACTION_H
#define	MSGACTION_H

#include <bitset>
#include "shared/network/MsgData.h"
#include "shared/network/MsgType.h"

#define TURN_HELM_NEGATIVE 0
#define TURN_HELM_POSITIVE 1
#define TURN_SAIL_NEGATIVE 2
#define TURN_SAIL_POSITIVE 3

class MsgAction : public MsgData {
public:
    explicit MsgAction(std::bitset<4> keys);
    virtual ~MsgAction();
};

#endif	/* MSG_ACTION_H */

