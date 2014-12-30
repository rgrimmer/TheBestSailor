#include <iostream>

#include "shared/network/MsgData.h"

#include "server/ServerPlayer.h"
#include "server/ServerPlayers.h"
#include "server/network/ServerMessageQueue.h"
#include "server/network/ServerUDPManager.h"

ServerUDPManager::ServerUDPManager(ServerPlayers& players, ServerMessageQueue& msgQueue)
: m_port(0)
, m_players(players)
, m_msgQueue(msgQueue)
, m_threadReceiver(nullptr) {

}

ServerUDPManager::~ServerUDPManager() {
    delete m_threadReceiver;
}

bool ServerUDPManager::initialize(unsigned short port) {
    std::cout << "[UDP][Init] \tInitialize udp socket" << std::endl;
    m_port = port;
    m_socket.setBlocking(true);
    sf::Socket::Status status = m_socket.bind(m_port);
    std::cout << "[UDP][Init] \tInitialize done" << std::endl;
    return status == sf::Socket::Done;
}

void ServerUDPManager::startReceiverThread() {
    m_threadReceiver = new std::thread(&ServerUDPManager::receiver, this);
}

void ServerUDPManager::receiver() {
    while (true) {
        MsgData *message = new MsgData();
        sf::IpAddress senderAddress;
        unsigned short senderPort;

        // Check status
        if (m_socket.receive(*message, senderAddress, senderPort) != sf::Socket::Done) {
            std::cout << " ! Error Socket Status not Done " << std::endl;
            return;
        }
        std::cout << "[UDP][Recv]";

        // Rebuild message
        ServerPlayer* player = m_players.getPlayer(senderAddress, senderPort);

        // Check validity
        if (player) {
            m_msgQueue.push(std::pair<ServerPlayer*, MsgData*>(player, message));

        } else if (!player) {
            std::cout << "\tAucun player pour : " << senderAddress.toString() << ":" << senderPort;
        } else {
            std::cout << "\tAucun message n'a pu être créé";
        }
        std::cout << std::endl;
    }
}

bool ServerUDPManager::send(MsgData &message, const ServerPlayer& player) const {
    sf::Socket::Status status = m_socket.send(message, player.getAddress(), player.getUdpPort());
    std::cout << "[UDP][Send] \t" /*<< message.getMsgType()*/ << std::endl;
    return (status == sf::Socket::Done);
}

bool ServerUDPManager::send(MsgData &message, const std::vector<ServerPlayer*>& players) const {
    bool receivedByAll = true;
    for (const auto player : players) {
        if (!send(message, *player)) {
            receivedByAll = false;
        }
    }
    return receivedByAll;
}
