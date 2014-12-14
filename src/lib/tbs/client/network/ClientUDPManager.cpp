#include <iostream>
#include <client/network/ClientUDPManager.h>

ClientUDPManager::ClientUDPManager() {

}

ClientUDPManager::~ClientUDPManager() {

}

void ClientUDPManager::initialize(const std::string& addressRemote, unsigned short portRemote) {
    m_address = addressRemote;
    m_port = portRemote;
//    m_socket.setBlocking(false); // @TODO remove ?
}

sf::Packet ClientUDPManager::receive() {
    sf::Packet packet;
    sf::IpAddress senderAddress;
    unsigned short senderPort;

    m_socket.receive(packet, senderAddress, senderPort);
    std::cout << "[UDP][Recv]" << std::endl;

    return packet;
}

bool ClientUDPManager::send(sf::Packet packet) {
    sf::Socket::Status status = m_socket.send(packet, m_address, m_port);
    std::cout << "[UDP][Send]" << std::endl;
    return (status == sf::Socket::Done);
}
