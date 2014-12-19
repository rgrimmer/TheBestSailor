#include <iostream>

#include <SFML/Network/Packet.hpp>

#include "shared/network/MessageData.h"
#include "shared/network/UtilsNetwork.h"
#include "shared/network/MsgFactory.h"

#include "client/network/ClientMsgQueue.h"
#include "client/network/ClientTCPManager.h"

ClientTCPManager::ClientTCPManager(ClientMsgQueue& msgQueue)
: m_msgQueue(msgQueue)
, m_threadReceiver(nullptr) {
    m_socket.setBlocking(true);
}

ClientTCPManager::~ClientTCPManager() {
    delete m_threadReceiver;
}

bool ClientTCPManager::connect(sf::IpAddress serverAdress, unsigned short serverPortTcp, sf::Time timeout) {
    std::cout << "[Conn][TCP] \tTry to establish connection with server" << std::endl;
    sf::Socket::Status status = m_socket.connect(serverAdress, serverPortTcp, timeout);
    return (status == sf::Socket::Done);
}

void ClientTCPManager::disconnect() {
    m_socket.disconnect();
}

void ClientTCPManager::startReceiverThread() {
    m_threadReceiver = new std::thread(&ClientTCPManager::receiver, this);
}

void ClientTCPManager::receiver() {
    while (true) {
        MessageData* msg = new MessageData();
        m_socket.receive(*msg);
        m_msgQueue.push(msg);
    }
}

bool ClientTCPManager::send(MessageData& message) const {
    std::cout << "[Send][TCP] \t" /*<< message.getType()*/ << std::endl;
    return (m_socket.send(message) == sf::Socket::Done);
}
