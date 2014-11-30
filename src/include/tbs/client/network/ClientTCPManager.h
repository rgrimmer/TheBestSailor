/* 
 * File:   ClientTCPManager.h
 * Author: remy
 *
 * Created on 30 novembre 2014, 13:34
 */

#ifndef CLIENT_TCP_MANAGER_H
#define	CLIENT_TCP_MANAGER_H

#include <SFML/Network.hpp>
class ClientTCPManager {
    
public:
    ClientTCPManager();
    ~ClientTCPManager();
    
    bool connect(void);
    void disconnect(void);
    
    bool send (sf::Packet packet);
    sf::Packet receive(void);
    
private:
    sf::TcpSocket m_socket;
};


#endif	/* CLIENTTCPMANAGER_H */

