/* 
 * File:   MsgAction.h
 * Author: remy
 *
 * Created on 26 décembre 2014, 13:51
 */

#ifndef MSG_ACTION_H
#include <bitset>
#include "shared/network/MessageData.h"
#include "shared/network/MsgType.h"

#define TURN_HELM_NEGATIVE 0
#define TURN_HELM_POSITIVE 1
#define TURN_SAIL_NEGATIVE 2
#define TURN_SAIL_POSITIVE 3

class MsgAction : public MessageData {
public:
    explicit MsgAction(std::bitset<4> keys);
    virtual ~MsgAction();
};

#endif	/* MSG_ACTION_H */

