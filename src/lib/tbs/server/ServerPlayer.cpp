#include <server/ServerPlayer.h>

//MsgClientPlayerInfo operator>>(MsgClientPlayerInfo &msg, ServerPlayer player) {
//    msg >>
//}

ServerPlayer::ServerPlayer()
: m_id(0)
, m_name("Anonymous")
, m_udpPort(0) {

}

ServerPlayer::~ServerPlayer() {
}

unsigned int ServerPlayer::getId() const {
    return m_id;
}

void ServerPlayer::setId(unsigned int id) {
    m_id = id;
}

void ServerPlayer::setUdpPort(unsigned short udpPort) {
    m_udpPort = udpPort;
}

const sf::TcpSocket& ServerPlayer::getTCPSocket() const {
    return m_TCPSocket;
}

sf::TcpSocket& ServerPlayer::getTCPSocket() {
    return m_TCPSocket;
}

sf::IpAddress ServerPlayer::getAddress() const {
    return m_TCPSocket.getRemoteAddress();
}

std::string ServerPlayer::getName() const {
    return m_name;
}

void ServerPlayer::setName(const std::string& name) {
    m_name = name;
}

unsigned short ServerPlayer::getUdpPort() const {
    return m_udpPort;
}