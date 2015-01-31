#include <iostream>

#include "shared/network/MsgData.h"

#include "client/network/ClientMsgQueue.h"
#include "client/network/ClientUDPManager.h"

ClientUDPManager::ClientUDPManager(ClientMsgQueue& msgQueue)
: m_msgQueue(msgQueue) {
    m_socket.bind(sf::Socket::AnyPort);
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
        MsgData* msg = new MsgData();
        sf::IpAddress senderAddress;
        unsigned short senderPort;

        m_socket.receive(*msg, senderAddress, senderPort);
        std::cout << "[UDP][Recv] \t";
        m_msgQueue.push(msg);
    }
}

bool ClientUDPManager::send(MsgData& message) const {
    sf::Socket::Status status = m_socket.send(message, m_addressRemote, m_portRemote);
    std::cout << "[UDP][Send] \tSend to " << m_addressRemote.toString() << ":" << m_portRemote /*<< message.getType()*/ << std::endl;
    return (status == sf::Socket::Done);
}
