/* 
 * File:   ServerNetwork.cpp
 * Author: maxence
 * 
 * Created on 13 décembre 2014, 13:32
 */

#include <iostream>

#include "shared/network/Message.h"
#include "shared/network/MsgTurnHelm.h"
#include "shared/network/MsgTurnSail.h"
#include "shared/network/MsgClientPlayerInfo.h"

#include "shared/network/UtilsNetwork.h"
#include "shared/SynchronizedQueue.h"

#include "server/PlayerList.h"
#include "server/game/ServerGame.h"
#include "server/network/ServerNetwork.h"
#include "server/network/ServerMessageQueue.h"

ServerNetwork::ServerNetwork(PlayerList& players)
: m_players(players)
, m_tcpManager(players, m_messageQueue, SERVER_PORT_TCP)
, m_udpManager(players, m_messageQueue) {

}

ServerNetwork::~ServerNetwork() {
}

ServerTCPManager& ServerNetwork::getTCPManager() {
    return m_tcpManager;
}

ServerUDPManager& ServerNetwork::getUDPManager() {
    return m_udpManager;
}

ServerMessageQueue& ServerNetwork::getMessageQueue() {
    return m_messageQueue;
}

void ServerNetwork::initialize() {
    std::cout << "[NetW][Init]" << std::endl;
    m_udpManager.initialize(SERVER_PORT_UDP);
    startTCPThread();
    startUDPThread();
}

void ServerNetwork::startTCPThread() {
    m_tcpManager.startReceiverThread();
}

void ServerNetwork::startUDPThread() {
    m_udpManager.startReceiverThread();
}
