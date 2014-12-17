#include <iostream>

#include <SFML/Network/Packet.hpp>

#include "shared/network/MessageData.h"
#include "shared/network/UtilsNetwork.h"
#include "shared/network/MsgFactory.h"

#include "client/network/ClientMsgQueue.h"
#include "client/network/ClientTCPManager.h"

ClientTCPManager::ClientTCPManager(ClientMsgQueue& msgQueue)
: m_msgQueue(msgQueue)
, m_threadReceiver(nullptr){

}

ClientTCPManager::~ClientTCPManager() {
    delete m_threadReceiver;
}

bool ClientTCPManager::connect(sf::IpAddress serverAdress, unsigned short serverPortTcp) {
    std::cout << "[Connect][TCP]\tEstablish connection with server" << std::endl;
    sf::Socket::Status status = m_socket.connect(serverAdress, serverPortTcp);
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
        sf::Packet packet;
        m_socket.receive(packet);
        MessageData* msg = MsgFactory::createMessage(packet);
        if (msg) {
            m_msgQueue.push(msg);
        }
    }
}

bool ClientTCPManager::send(const MessageData& message) const {
    std::cout << "[Send][TCP] \t" << message.getType() << std::endl;
    sf::Packet packet;
    return (m_socket.send(message.toPacketWithType(packet)) == sf::Socket::Done);
}
