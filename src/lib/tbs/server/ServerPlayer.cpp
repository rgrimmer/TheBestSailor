#include <server/ServerPlayer.h>

ServerPlayer::ServerPlayer(unsigned int id, std::string name, sf::TcpSocket* socket) : m_id(id), m_name(name), m_TCPSocket(socket){
    m_address = m_TCPSocket->getRemoteAddress();
    m_udpPort = 0;
}

ServerPlayer::~ServerPlayer() {
    
}

void ServerPlayer::setUdpPort(unsigned short udpPort) {
    m_udpPort = udpPort;
}

sf::TcpSocket* ServerPlayer::getTCPSocket() const {
    return m_TCPSocket;
}

sf::IpAddress ServerPlayer::getAddress() const {
    return m_address;
}

std::string ServerPlayer::getName() const {
    return m_name;
}

unsigned short ServerPlayer::getUdpPort() const{
    return m_udpPort;
}