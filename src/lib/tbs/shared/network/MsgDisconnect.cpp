/* 
 * File:   MsgDisconnect.cpp
 * Author: maxence
 * 
 * Created on 11 décembre 2014, 21:28
 */

#include "shared/network/MsgDisconnect.h"

MsgDisconnect::MsgDisconnect()
: MsgData(MsgType::Disconnect) {
}

MsgDisconnect::~MsgDisconnect() {
}
