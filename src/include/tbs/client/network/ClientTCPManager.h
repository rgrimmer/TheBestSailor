/* 
 * File:   ClientTCPManager.h
 * Author: remy
 *
 * Created on 30 novembre 2014, 13:34
 */

#ifndef CLIENT_TCP_MANAGER_H
#define	CLIENT_TCP_MANAGER_H

#include <thread>
#include <SFML/Network/IpAddress.hpp>
#include <SFML/Network/TcpSocket.hpp>
#include <SFML/System/Time.hpp>

class MessageData;
class ClientMsgQueue;

class ClientTCPManager {
public:
    ClientTCPManager(ClientMsgQueue& msgQueue);
    ~ClientTCPManager();

    bool connect(sf::IpAddress serverAdress, unsigned short serverPortTcp, sf::Time timout = sf::Time::Zero);
    void disconnect(void);

    void startReceiverThread();
    bool send(MessageData &message) const;

private:
    void receiver();
    
private:
    mutable sf::TcpSocket m_socket;
    ClientMsgQueue& m_msgQueue;
            
    std::thread* m_threadReceiver;
};


#endif	/* CLIENTTCPMANAGER_H */

