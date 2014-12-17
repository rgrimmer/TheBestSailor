#include <server/ServerPlayer.h>

ServerPlayer::ServerPlayer() {

}

ServerPlayer::ServerPlayer(unsigned int id, const std::string &name, sf::TcpSocket& socket) 
: m_id(id)
, m_name(name)
, m_TCPSocket(&socket){
    m_address = m_TCPSocket->getRemoteAddress();
    m_udpPort = 0;
}

ServerPlayer::~ServerPlayer() {
    
}

unsigned int ServerPlayer::getId() const {
    return m_id;
}

void ServerPlayer::setUdpPort(unsigned short udpPort) {
    m_udpPort = udpPort;
}

sf::TcpSocket& ServerPlayer::getTCPSocket() const {
    return *m_TCPSocket;
}

sf::IpAddress ServerPlayer::getAddress() const {
    return m_address;
}

std::string ServerPlayer::getName() const {
    return m_name;
}

void ServerPlayer::setName(const std::string& name) {
    m_name = name;
}

unsigned short ServerPlayer::getUdpPort() const{
    return m_udpPort;
}