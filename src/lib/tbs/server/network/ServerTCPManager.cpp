#include <iostream>

#include <shared/network/Request.h>
#include <server/network/ServerTCPManager.h>

#include <shared/Utils.h>

ServerTCPManager::ServerTCPManager() {
    m_clientsCount = 0;
}

ServerTCPManager::~ServerTCPManager() {

}

bool ServerTCPManager::send(sf::Packet packet, sf::TcpSocket* player) {
    sf::Socket::Status status = player->send(packet);
    return (status == sf::Socket::Done);
}

bool ServerTCPManager::waitConnections(unsigned short port, sf::Packet mapPacket, std::vector<ServerPlayer*>& players, sf::Time timeout) {

    if (m_listener.listen(port) != sf::Socket::Done) {
        return false;
    }
    m_selector.add(m_listener);

    while (m_selector.wait(timeout)) {

        for (int i = 0; i < m_clientsCount; ++i) {

            if (m_selector.isReady(m_clients[i])) {
                std::cout << "[recv] ";
                sf::Packet packetNewPlayer;
                sf::TcpSocket::Status s = m_clients[i].receive(packetNewPlayer);

                if (s == sf::TcpSocket::Done) {
                    sf::Uint8 req;
                    packetNewPlayer >> req;

                    if (req == REQ_NEW_PLAYER) {
                        std::cout << "New Player" << std::endl;
                        std::string name;
                        packetNewPlayer >> name;
                        std::cout << "added new player : " << name << std::endl;
                        players.push_back(new ServerPlayer(i, name, &m_clients[i]));

                    } else {
                        std::cout << "Undefined Request" << std::endl;
                        return false;
                    }

                }
                if (s == sf::TcpSocket::Disconnected) {
                    std::cout << "player Disconnected" << std::endl;
                    m_selector.remove(m_clients[i]);
                    i--;
                } else if (s == sf::TcpSocket::Error) {
                    std::cout << "Error recv" << std::endl;
                    return false;
                } else {
                    m_clients[i].send(mapPacket);
                }
            }
        }

        if (m_clientsCount < NB_CLIENT_MAX && m_selector.isReady(m_listener)) {
            if (m_listener.accept(m_clients[m_clientsCount]) != sf::Socket::Done) {
                std::cout << "Error accept" << std::endl;
                return false;
            }

            std::cout << "new player connected" << std::endl;
            m_selector.add(m_clients[m_clientsCount]);
            m_clientsCount++;
        }
    }
    m_selector.remove(m_listener);
    m_listener.close();

    return true;
}