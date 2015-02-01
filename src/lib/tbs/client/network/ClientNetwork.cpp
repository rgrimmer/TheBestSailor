/* 
 * File:   ClientNetwork.cpp
 * Author: maxence
 * 
 * Created on 14 décembre 2014, 17:26
 */

#include <iostream>

#include <SFML/System/Sleep.hpp>
#include <SFML/System/Clock.hpp>

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

void ClientNetwork::disconnect() {
    m_tcpManager.disconnect();
}

bool ClientNetwork::connect(const sf::IpAddress &address, unsigned short port, sf::Time timeout) {
    sf::Time minTime = sf::milliseconds(1000);
    if (timeout < minTime)
        timeout = minTime;

    if (m_tcpManager.connect(address, port, timeout)) {
        std::cout << "[NetW][Tcp] \tConnection established" << std::endl;
        return true;
    }
    std::cout << "[NetW][Tcp] \tCan't find server @" << address.toString() << std::endl;
    return false;
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