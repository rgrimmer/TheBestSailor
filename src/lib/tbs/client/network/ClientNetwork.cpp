/* 
 * File:   ClientNetwork.cpp
 * Author: maxence
 * 
 * Created on 14 décembre 2014, 17:26
 */

#include <iostream>

#include <SFML/System/Sleep.hpp>

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

void ClientNetwork::connect(const sf::IpAddress &address) {
    while (!m_tcpManager.connect(address, SERVER_PORT_TCP/*, sf::milliseconds(1000)*/)) {
        std::cout << "[NetW][Tcp] \tCan't find server, try again in 5s" << std::endl;
        sf::sleep(sf::milliseconds(5000));
    }
    std::cout << "[NetW][Tcp] \tConnection established" << std::endl;
}

void ClientNetwork::initialize() {
    startTcpReceiverThread();
    startUdpReceiverThread();
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