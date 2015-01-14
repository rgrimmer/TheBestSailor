/* 
 * File:   ServerNetwork.cpp
 * Author: maxence
 * 
 * Created on 13 décembre 2014, 13:32
 */

#include <iostream>

#include "shared/network/UtilsNetwork.h"

#include "server/ServerPlayers.h"
#include "server/network/ServerNetwork.h"

ServerNetwork::ServerNetwork(ServerPlayers& players)
: m_players(players)
, m_tcpManager(players, m_messageQueue)
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
    m_tcpManager.initialize(SERVER_PORT_TCP);
    m_udpManager.initialize();
    startTCPThread();
    startUDPThread();
}

void ServerNetwork::startTCPThread() {
    m_tcpManager.startReceiverThread();
}

void ServerNetwork::startUDPThread() {
    m_udpManager.startReceiverThread();
}
