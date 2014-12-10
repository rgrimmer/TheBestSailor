#include <iostream>

#include <shared/network/Request.h>
#include <server/network/ServerTCPManager.h>

#include <shared/Utils.h>

ServerTCPManager::ServerTCPManager() {
    m_clientsCount = 0;
}

ServerTCPManager::~ServerTCPManager() {

}

bool ServerTCPManager::initialize(unsigned short port) {

    m_port = port;

    if (m_listener.listen(m_port) != sf::Socket::Done) {
        return false;
    }
    m_selector.add(m_listener);
    return true;
}

bool ServerTCPManager::send (sf::Packet packet, sf::TcpSocket* player) {
    sf::Socket::Status status = player->send(packet);
    return(status == sf::Socket::Done);
}

bool ServerTCPManager::waitConnections(sf::Packet mapPacket, std::vector<ServerPlayer*>& players) {
    bool stay = true;

    while (stay) {
        stay = false;

        if (m_selector.wait(sf::seconds(5.0f))) {
            stay = true;
            for (int i = 0; i < m_clientsCount; ++i) {

                if (m_selector.isReady(m_clients[i])) {
                    sf::Packet packetNewPlayer;
                    sf::TcpSocket::Status s = m_clients[i].receive(packetNewPlayer);

                    if (s == sf::TcpSocket::Done) {
                        sf::Uint8 req;
                        packetNewPlayer >> req;

                        if (req == REQ_NEW_PLAYER) {
                            std::string name;
                            packetNewPlayer >> name;
                            std::cout << "added new player : " << name << std::endl;
                            players.push_back(new ServerPlayer(i, name, &m_clients[i]));
                            
                        } else {
                            return false;
                        }

                    }
                    if (s == sf::TcpSocket::Disconnected) {
                        std::cout << "player disconnected" << std::endl;
                        m_selector.remove(m_clients[i]);
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

    }

    m_listener.close();

    return true;
}