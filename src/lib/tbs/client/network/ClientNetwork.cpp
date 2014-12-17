/* 
 * File:   ClientNetwork.cpp
 * Author: maxence
 * 
 * Created on 14 décembre 2014, 17:26
 */

#include <iostream>

#include "shared/network/UtilsNetwork.h"

#include "client/network/ClientTCPManager.h"
#include "client/network/ClientUDPManager.h"
#include "client/network/ClientNetwork.h"

ClientNetwork::ClientNetwork()
: m_tcpManager(m_msgQueue)
, m_udpManager(m_msgQueue) {
}

ClientNetwork::~ClientNetwork() {
}

ClientMsgQueue& ClientNetwork::getMessageQueue() {
    return m_msgQueue;
}

void ClientNetwork::connect() {
    m_tcpManager.connect(sf::IpAddress("localhost"), SERVER_PORT_TCP);
}

void ClientNetwork::startTcpReceiverThread() {
    m_tcpManager.startReceiverThread();
}

void ClientNetwork::startUdpReceiverThread() {
    m_udpManager.startReceiverThread();
}

ClientTCPManager& ClientNetwork::getTcpManager() {
    return m_tcpManager;
}

const ClientTCPManager& ClientNetwork::getTcpManager() const {
    return m_tcpManager;
}

ClientUDPManager& ClientNetwork::getUdpManager() {
    return m_udpManager;
}

const ClientUDPManager& ClientNetwork::getUdpManager() const {
    return m_udpManager;
}