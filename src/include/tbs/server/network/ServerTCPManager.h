/* 
 * File:   ServerTCPManager.h
 * Author: remy
 *
 * Created on 30 novembre 2014, 15:36
 */

#ifndef SERVER_TCP_MANAGER_H
#define	SERVER_TCP_MANAGER_H

#include <thread>

#include <SFML/Network/TcpListener.hpp>
#include <SFML/Network/SocketSelector.hpp>

class ServerPlayers;
class ServerMessageQueue;
class MsgData;
class ServerPlayer;

class ServerTCPManager {
public:
    ServerTCPManager(ServerPlayers &players, ServerMessageQueue& msgQueue);
    ~ServerTCPManager();
    
    unsigned short getPort() const;

    void initialize(unsigned short portTcp);
    void startReceiverThread();
    bool send(MsgData &message, sf::TcpSocket& player) const;
    bool send(MsgData &message, const std::vector<ServerPlayer*>& players) const;

private:
    void receiver();
    bool receiveConnection();
    void receiveCommunication(ServerPlayer& player);

    sf::TcpListener m_listener;
    sf::SocketSelector m_selector;

    std::thread* m_threadReceiver;

    ServerPlayers &m_players;
    ServerMessageQueue& m_msgQueue;
};


#endif	/* SERVER_TCP_MANAGER_H */

