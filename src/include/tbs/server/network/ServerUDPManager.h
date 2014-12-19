/* 
 * File:   ServerUDPManager.h
 * Author: remy
 *
 * Created on 30 novembre 2014, 15:36
 */

#ifndef SERVER_UDP_MANAGER_H
#define	SERVER_UDP_MANAGER_H

#include <thread>
#include <vector>

#include <SFML/Network/UdpSocket.hpp>

class ServerPlayers;
class ServerMessageQueue;
class MessageData;
class ServerPlayer;

class ServerUDPManager {
public:
    ServerUDPManager(ServerPlayers& players, ServerMessageQueue& msgQueue);
    ~ServerUDPManager();

    bool initialize(unsigned short port);

    void startReceiverThread();
    bool send(MessageData &message, const ServerPlayer& player) const;
    bool send(MessageData &message, const std::vector<ServerPlayer*>& players) const;

private:
    void receiver();

private:
    unsigned short m_port;
    mutable sf::UdpSocket m_socket;

    ServerPlayers& m_players;
    ServerMessageQueue& m_msgQueue;

    std::thread* m_threadReceiver;
};

#endif	/* SERVER_UDP_MANAGER_H */

