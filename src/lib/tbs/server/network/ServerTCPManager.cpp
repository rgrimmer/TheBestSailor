#include <iostream>

#include "server/network/ServerTCPManager.h"


#include <SFML/Network/TcpSocket.hpp>

#include "shared/network/Semaphore.h"
#include "shared/network/MessageData.h"
#include "shared/network/MsgFactory.h"

#include "server/ServerPlayer.h"
#include "server/ServerPlayers.h"
#include "server/network/ServerMessageQueue.h"
#include "shared/network/MsgDisconnect.h"

ServerTCPManager::ServerTCPManager(ServerPlayers& players, ServerMessageQueue& msgQueue)
: m_threadReceiver(nullptr)
, m_players(players)
, m_msgQueue(msgQueue) {
}

ServerTCPManager::~ServerTCPManager() {

}

unsigned short ServerTCPManager::getPort() const {
    return m_listener.getLocalPort();
}

void ServerTCPManager::initialize(unsigned short portTcp) {
    std::cout << "[TCP][Init] \tInitialize tcp socket" << std::endl;
    // Start listener tcp
    if (m_listener.listen(portTcp) != sf::Socket::Done) {
        std::cerr << "ERROR : CAN'T READ TCP SOCKET" << std::endl;
    }
    m_selector.add(m_listener);
    std::cout << "[TCP][Init] \tInitialize done" << std::endl;
}

void ServerTCPManager::startReceiverThread() {
    std::cout << "[TCP][Start] \tStart receiver thread" << std::endl;
    delete m_threadReceiver;
    m_threadReceiver = new std::thread(&ServerTCPManager::receiver, this);
    std::cout << "[TCP][Start] \tStart receiver thread done" << std::endl;
}

void ServerTCPManager::receiver() {
    std::cout << "[TCP][Thread] \treceiver started" << std::endl;
    while (true) {
        m_selector.wait();
        if (m_selector.isReady(m_listener)) {
            receiveConnection();
        }

        for (auto* player : m_players.getList()) {

            if (m_selector.isReady(player->getTCPSocket())) {
                std::cout << "[TCP][Thread] \t " << player << " " << player->getName() << "@" << player->getAddress() << ":" << player->getTCPSocket().getRemotePort() << " is ready" << std::endl;
                receiveCommunication(*player);
            }
        }
    }
    std::cout << "[TCP][Thread] \treceiver ended" << std::endl;
}

bool ServerTCPManager::send(MessageData &message, sf::TcpSocket& player) const {
    std::cout << "[Send][Tcp] \t"/* << message.getMsgType()*/ << std::endl;
    return (player.send(message) == sf::Socket::Done);
}

bool ServerTCPManager::send(MessageData &message, const std::vector<ServerPlayer*>& players) const {
    bool hasReceiveByAll = true;
    for (auto &player : players) {
        if (send(message, player->getTCPSocket()) != sf::Socket::Done) {
            hasReceiveByAll = false;
        }
    }
    return hasReceiveByAll;
}

bool ServerTCPManager::receiveConnection() {
    //    if (m_players.getList().size() < NB_CLIENT_MAX) {
    // Register client

    std::cout << "[TCP][Recv][Con][Start] \t Receveive connection started" << std::endl;
    ServerPlayer& player = m_players.addNewPlayer();
    sf::TcpSocket& playerSocket = player.getTCPSocket();
    std::cout << "[TCP][Recv][Con] \t Add new player done" << std::endl;
    if (m_listener.accept(playerSocket) != sf::Socket::Done) {
        std::cout << "Error accept" << std::endl;
        return false;
    } else {
        m_selector.add(playerSocket);
        std::cout << "[TCP][Recv][Con][End] \t Receive connection done" << std::endl;
        return true;
    }
}

void ServerTCPManager::receiveCommunication(ServerPlayer &player) {
    MessageData *message = new MessageData();
    sf::TcpSocket::Status s = player.getTCPSocket().receive(*message);

    std::cout << "[TCP][Recv] \t Receive message from " << player.getName() << std::endl;

    if (s == sf::TcpSocket::Done) {
        m_msgQueue.push(std::pair<ServerPlayer*, MessageData*>(&player, message));

    } else if (s == sf::TcpSocket::Disconnected) {
        std::cout << "Player Disconnected" << std::endl;
        m_selector.remove(player.getTCPSocket());
        *message << MsgType::Disconnect;
        m_msgQueue.push(std::pair<ServerPlayer*, MessageData*>(&player, message));

    } else if (s == sf::TcpSocket::Error) {
        std::cout << "Error Recv" << std::endl;
        delete message;
    } else {
        std::cout << "Error Invalide status : " << s << std::endl;
        delete message;
    }
}
