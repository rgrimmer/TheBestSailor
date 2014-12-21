#include <server/ServerPlayer.h>

//MsgClientPlayerInfo operator>>(MsgClientPlayerInfo &msg, ServerPlayer player) {
//    msg >>
//}

ServerPlayer::ServerPlayer()
: m_id(-1)
, m_name("Anonymous")
, m_address(sf::IpAddress::None)
, m_udpPort(0)
, m_TCPSocket(nullptr) {

}

ServerPlayer::ServerPlayer(unsigned int id, const std::string &name, sf::TcpSocket& socket)
: m_id(id)
, m_name(name)
, m_address(socket.getRemoteAddress())
, m_udpPort(0)
, m_TCPSocket(&socket) {
}

ServerPlayer::~ServerPlayer() {
    delete m_TCPSocket;
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
    return m_TCPSocket->getRemoteAddress();
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

void ServerPlayer::initialize() {
    delete m_TCPSocket;
    m_TCPSocket = new sf::TcpSocket();
}
