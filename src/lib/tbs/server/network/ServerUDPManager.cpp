#include <iostream>

#include <server/network/ServerUDPManager.h>

#include <shared/Utils.h>
#include <shared/network/Message.h>

#include "server/PlayerList.h"
#include "shared/network/MsgFactory.h"

ServerUDPManager::ServerUDPManager(PlayerList& players, ServerMessageQueue& msgQueue)
: m_port(0)
, m_players(players)
, m_msgQueue(msgQueue)
, m_threadReceiver(nullptr)
 {

}

ServerUDPManager::~ServerUDPManager() {
    delete m_threadReceiver;
}

bool ServerUDPManager::initialize(unsigned short port) {
    m_port = port;
    m_socket.setBlocking(true);
    sf::Socket::Status status = m_socket.bind(m_port);
    std::cout << "[UDP][Init]" << std::endl;
    return status == sf::Socket::Done;
}

void ServerUDPManager::startReceiverThread() {
    m_threadReceiver = new std::thread(&ServerUDPManager::receiver, this);
}

void ServerUDPManager::receiver() {
    sf::Packet packet;
    sf::IpAddress senderAddress;
    unsigned short senderPort;

    // Check status
    if (m_socket.receive(packet, senderAddress, senderPort) != sf::Socket::Done) {
        std::cout << " ! Error Socket Status not Done " << std::endl;
        return;
    }
    std::cout << "[UDP][Recv]";

    // Rebuild message
    MessageData* msg = MsgFactory::createMessage(packet);
    ServerPlayer* player = m_players.getPlayer(senderAddress, senderPort);

    // Check validity
    if (player && msg) {
        m_msgQueue.push(std::pair<ServerPlayer*, MessageData*>(player, msg));

    } else if (!player) {
        std::cout << "\tAucun player pour : " << senderAddress.toString() << ":" << senderPort;
    } else {
        std::cout << "\tAucun message n'a pu être créé";
    }
    std::cout << std::endl;
}

bool ServerUDPManager::send(const MessageData &message, const ServerPlayer& player) const {
    sf::Packet packet;
    sf::Socket::Status status = m_socket.send(message.toPacketWithType(packet), player.getAddress(), player.getUdpPort());
    std::cout << "[UDP][Send] \t" << message.getType() << std::endl;
    return (status == sf::Socket::Done);
}

bool ServerUDPManager::send(const MessageData &message, const std::vector<ServerPlayer*>& players) const {
    bool receivedByAll = true;
    for (const auto player : players) {
        if (!send(message, *player)) {
            receivedByAll = false;
        }
    }
    return receivedByAll;
}
