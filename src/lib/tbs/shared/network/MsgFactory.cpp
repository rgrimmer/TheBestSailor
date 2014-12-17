/* 
 * File:   MsgFactory.cpp
 * Author: maxence
 * 
 * Created on 16 décembre 2014, 00:40
 */
#include <iostream>

#include "shared/network/MsgFactory.h"
#include "shared/network/MessageData.h"
#include "shared/network/MsgClientPlayerInfo.h"
#include "shared/network/MsgServerPlayerInfo.h"
#include "shared/network/MsgDisconnect.h"
#include "shared/network/MsgTurnHelm.h"
#include "shared/network/MsgTurnSail.h"

MessageData* MsgFactory::createMessage(sf::Packet& packet) {
    MsgType msgType = MessageData::popType(packet);
    MessageData* message;
//    MsgTurnHelm* msgHelm = new MsgTurnHelm();
//    switch (msgType) {
//        case MsgType::MSG_ACK:
//            message = nullptr;
//            break;
//        case MsgType::MSG_ACTION_TURN_HELM:
//            packet >> *msgHelm;
//            message = msg;
//            break;
//        case MsgType::MSG_ACTION_TURN_SAIL:
//            MsgTurnSail* msg = new MsgTurnSail();
//            packet >> *msg;
//            message = msg;
//            break;
//        case MsgType::MSG_CLIENT_PLAYER_INFO:
//            MsgClientPlayerInfo* msg = new MsgClientPlayerInfo();
//            packet >> *msg;
//            message = msg;
//            break;
//        case MsgType::MSG_SERVER_PLAYER_INFO:
//            auto* msg = new MsgServerPlayerInfo();
//            packet >> *msg;
//            message = msg;
//            break;
//        case MsgType::MSG_DISCONNECT:
//            auto* msg = new MsgDisconnect();
//            packet >> *msg;
//            message = msg;
//            break;
//        case MsgType::MSG_UNDEF:
//            std::cout << "Undefined Type" << std::endl;
//            message = nullptr;
//            break;
//        default:
//            std::cerr << "Unexist Type" << std::endl;
//            message = nullptr;
//    }
    return message;
}
