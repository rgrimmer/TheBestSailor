#include <iostream>

#include "shared/network/MsgFactory.h"
#include "shared/network/MessageData.h"

#include "client/network/ClientMsgQueue.h"
#include "client/network/ClientUDPManager.h"

ClientUDPManager::ClientUDPManager(ClientMsgQueue& msgQueue)
: m_msgQueue(msgQueue) {

}

ClientUDPManager::~ClientUDPManager() {

}

void ClientUDPManager::initialize(const sf::IpAddress& addressRemote, unsigned short portRemote) {
    m_addressRemote = addressRemote;
    m_portRemote = portRemote;
    m_socket.setBlocking(true);
}

unsigned short ClientUDPManager::getPort() const {
    return m_socket.getLocalPort();
}

void ClientUDPManager::startReceiverThread() {
    m_threadReceiver = new std::thread(&ClientUDPManager::receiver, this);
}

void ClientUDPManager::receiver() {
    while (true) {
        sf::Packet packet;
        sf::IpAddress senderAddress;
        unsigned short senderPort;

        m_socket.receive(packet, senderAddress, senderPort);
        std::cout << "[UDP][Recv] \t";
        if (senderAddress == m_addressRemote && senderPort == m_portRemote) {
            MessageData* msg = MsgFactory::createMessage(packet);
            if (msg) {
                std::cout << msg->getType() << std::endl;
                m_msgQueue.push(msg);
            } else {
                std::cout << "WARNING : Unreading message" << std::endl;
            }
        } else {
            std::cout << "WARNING : Message Source isn't server" << std::endl;
        }
    }
}

bool ClientUDPManager::send(const MessageData& message) const {
    sf::Packet packet;
    message.toPacketWithType(packet);
    sf::Socket::Status status = m_socket.send(packet, m_addressRemote, m_portRemote);
    std::cout << "[UDP][Send] \t" << message.getType() << std::endl;
    return (status == sf::Socket::Done);
}
