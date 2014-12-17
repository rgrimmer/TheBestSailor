#include <iostream>

#include "server/network/ServerTCPManager.h"


#include <SFML/Network/TcpSocket.hpp>

#include "shared/network/Semaphore.h"
#include "shared/network/MessageData.h"
#include "shared/network/MsgFactory.h"

#include "server/ServerPlayer.h"
#include "server/PlayerList.h"
#include "server/network/ServerMessageQueue.h"

ServerTCPManager::ServerTCPManager(PlayerList& playerList, ServerMessageQueue& msgQueue, unsigned short portTcp)
: m_threadReceiver(nullptr)
, m_players(playerList)
, m_msgQueue(msgQueue) {

    // Start listener tcp
    if (m_listener.listen(portTcp) != sf::Socket::Done) {
        std::cerr << "ERROR : CAN'T READ TCP SOCKET" << std::endl;
    }
    m_selector.add(m_listener);
}

ServerTCPManager::~ServerTCPManager() {

}

unsigned short ServerTCPManager::getPort() const {
    return m_listener.getLocalPort();
}


void ServerTCPManager::startReceiverThread() {
    m_threadReceiver = new std::thread(&ServerTCPManager::receiver, this);
}

void ServerTCPManager::receiver() {
    while (true) {
        m_selector.wait();
        if (m_selector.isReady(m_listener)) {
            receiveConnection();
        }

        for (auto& player : m_players.getList()) {

            if (m_selector.isReady(player.getTCPSocket())) {
                receiveCommunication(player);
            }
        }
    }
}

bool ServerTCPManager::send(const MessageData &message, sf::TcpSocket& player) const {
    sf::Packet packet;
    return (player.send(message.toPacketWithType(packet)) == sf::Socket::Done);
}

bool ServerTCPManager::send(const MessageData &message, const std::vector<ServerPlayer*>& players) const {
    bool hasReceiveByAll = true;
    for (const auto &player : players) {
        if (send(message, player->getTCPSocket()) != sf::Socket::Done) {
            hasReceiveByAll = false;
        }
    }
    return hasReceiveByAll;
}

bool ServerTCPManager::receiveConnection() {
//    if (m_players.getList().size() < NB_CLIENT_MAX) {
        // Register client
        ServerPlayer& player = m_players.addNewPlayer();
        if (m_listener.accept(player.getTCPSocket()) != sf::Socket::Done) {
            std::cout << "Error accept" << std::endl;
            return false;
        }
        std::cout << "new player connected" << std::endl;
        m_selector.add(player.getTCPSocket());

        return true;
//    } else {
//        std::cout << "Error : maximum client limit" << std::endl;
//    }
//    return false;
}

void ServerTCPManager::receiveCommunication(ServerPlayer &player) {
    std::cout << "[recv] ";
    sf::Packet packet;
    sf::TcpSocket::Status s = player.getTCPSocket().receive(packet);

    if (s == sf::TcpSocket::Done) {

        MessageData* msgData = MsgFactory::createMessage(packet);
        if (msgData) {
            std::pair<ServerPlayer*, MessageData*> tmp(&player, msgData);
            m_msgQueue.push(tmp);
        }

    } else if (s == sf::TcpSocket::Disconnected) {
        std::cout << "Player Disconnected" << std::endl;
        // @TODO Remove player
    } else if (s == sf::TcpSocket::Error) {
        std::cout << "Error Recv" << std::endl;
    } else {
        std::cout << "Error Invalide status : " << s << std::endl;
    }
}
