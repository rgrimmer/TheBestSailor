
#include <client/network/ClientUDPManager.h>

ClientUDPManager::ClientUDPManager() {

}

ClientUDPManager::~ClientUDPManager() {

}

void ClientUDPManager::initialize(const std::string& address, unsigned short port) {
    m_address = address;
    m_port = port;
    m_socket.setBlocking(false);
}

bool ClientUDPManager::send(sf::Packet packet) {
    sf::Socket::Status status = m_socket.send(packet, m_address, m_port);
    return (status == sf::Socket::Done);
}

sf::Packet ClientUDPManager::receive() {
    sf::Packet packet;
    sf::IpAddress senderAddress;
    unsigned short senderPort;

    m_socket.receive(packet, senderAddress, senderPort);

    return packet;
}