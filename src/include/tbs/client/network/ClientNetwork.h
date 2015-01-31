/* 
 * File:   ClientNetwork.h
 * Author: maxence
 *
 * Created on 14 décembre 2014, 17:26
 */

#ifndef CLIENTNETWORK_H
#define	CLIENTNETWORK_H

#include <SFML/Network/IpAddress.hpp>

#include "client/network/ClientTCPManager.h"
#include "client/network/ClientUDPManager.h"
#include "client/network/ClientMsgQueue.h"

class ClientNetwork {
public:
    ClientNetwork();
    virtual ~ClientNetwork();

    bool connect(const sf::IpAddress &address, unsigned short port, sf::Time timeout = sf::Time::Zero);
    void initialize();
    ClientTCPManager& getTcpManager();
    const ClientTCPManager& getTcpManager() const;
    ClientUDPManager& getUdpManager();
    const ClientUDPManager& getUdpManager() const;
    ClientMsgQueue& getMessageQueue();

private:
    void startTcpReceiverThread();
    void startUdpReceiverThread();

private:
    ClientTCPManager m_tcpManager;
    ClientUDPManager m_udpManager;

    ClientMsgQueue m_msgQueue;
};

#endif	/* CLIENTNETWORK_H */

