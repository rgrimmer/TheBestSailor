#include <iostream>

#include <SFML/Network/Packet.hpp>

#include "shared/network/MsgData.h"

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
        MsgData* msg = new MsgData();
        switch (m_socket.receive(*msg)) {
            case sf::Socket::Status::Done:
            {
                m_msgQueue.push(msg);
            }
                break;
            case sf::Socket::Status::Disconnected:
            {
                // @TODO
                std::cout << "[TCP][Recv] \t TCP Server connection disconnected" << std::endl;
                exit(-1);
            }
                break;
            case sf::Socket::Status::Error:
            {
                std::cout << "[TCP][Recv] \t TCP receive error" << std::endl;
            }
            case sf::Socket::Status::NotReady:
            {
//                std::cout << "[TCP][Recv] \t TCP not ready" << std::endl;
            }
                break;
            default :
                std::cout << "[TCP][Recv] \t TCP Unknow status error" << std::endl;
        }
    }
}

bool ClientTCPManager::send(MsgData& message) const {
    std::cout << "[Send][TCP] \t" /*<< message.getMsgType()*/ << std::endl;
    return (m_socket.send(message) == sf::Socket::Done);
}
