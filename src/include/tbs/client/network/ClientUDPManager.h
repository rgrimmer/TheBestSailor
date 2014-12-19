/* 
 * File:   ClientUDPManager.h
 * Author: remy
 *
 * Created on 30 novembre 2014, 14:13
 */

#ifndef CLIENT_UDP_MANAGER_H
#define	CLIENT_UDP_MANAGER_H

#include <thread>
#include <SFML/Network/Packet.hpp>
#include <SFML/Network/UdpSocket.hpp>
#include <SFML/Network/IpAddress.hpp>

class ClientMsgQueue;
class MessageData;

class ClientUDPManager {
public:
    ClientUDPManager(ClientMsgQueue& msgQueue);
    ~ClientUDPManager();

    void initialize(const sf::IpAddress& addressRemote, unsigned short portRemote);
    unsigned short getPort() const;

    void startReceiverThread();
    bool send(MessageData &message) const;


private:
    void receiver();

private:
    ClientMsgQueue& m_msgQueue;

    sf::IpAddress m_addressRemote;
    unsigned short m_portRemote;

    std::thread* m_threadReceiver;

    mutable sf::UdpSocket m_socket;

};

#endif	/* CLIENTUDPMANAGER_H */

