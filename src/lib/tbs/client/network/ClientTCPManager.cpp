#include <client/network/ClientTCPManager.h>

#include <shared/Utils.h>
#include <SFML/Network/Packet.hpp>

ClientTCPManager::ClientTCPManager() {
    
}

ClientTCPManager::~ClientTCPManager() {

}

bool ClientTCPManager::connect() {
    sf::Socket::Status status = m_socket.connect("localhost", SERVER_PORT_TCP);    
    return(status == sf::Socket::Done);
}

void ClientTCPManager::disconnect() {
    m_socket.disconnect();
}

bool ClientTCPManager::send(sf::Packet packet) {
    sf::Socket::Status status = m_socket.send(packet);
    return(status == sf::Socket::Done);
}

sf::Packet ClientTCPManager::receive() {
    sf::Packet packet;
    m_socket.receive(packet);
    return packet;
}