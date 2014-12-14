#include <iostream>

#include <shared/network/Request.h>
#include <shared/network/UtilsNetwork.h>

#include <server/network/ServerTCPManager.h>

#include "shared/network/Semaphore.h"

ServerTCPManager::ServerTCPManager() {
    m_clientsCount = 0;
}

ServerTCPManager::~ServerTCPManager() {

}

bool ServerTCPManager::send(sf::Packet packet, sf::TcpSocket* player) {
    sf::Socket::Status status = player->send(packet);
    return (status == sf::Socket::Done);
}

bool ServerTCPManager::send(sf::Packet packet, std::vector<ServerPlayer*> players) {
    bool isReceiveByAll = true;
    for (const auto &player : players) {
        if (player->getTCPSocket()->send(packet) != sf::Socket::Done)
            isReceiveByAll = false;
    }
    return isReceiveByAll;
}

bool ServerTCPManager::waitConnections(unsigned short port, std::vector<ServerPlayer*>& players, sf::Time timeout) {

    if (m_listener.listen(port) != sf::Socket::Done) {
        return false;
    }
    m_selector.add(m_listener);

    while (m_selector.wait(timeout)) {

        if (m_selector.isReady(m_listener)) {
            receiveNewConnection();
        }


        for (int i = 0; i < m_clientsCount; ++i) {

            if (m_selector.isReady(m_clients[i])) {
                receiveCommunication(i, players);
            }
        }
    }
    m_selector.remove(m_listener);
    m_listener.close();

    return true;
}

void ServerTCPManager::waitAcknowledgment(int permits) {
    m_acknowledgment.aquire(permits);
}

bool ServerTCPManager::receiveNewConnection() {
    if (m_clientsCount < NB_CLIENT_MAX) {
//        m_listner.a
        if (m_listener.accept(m_clients[m_clientsCount]) != sf::Socket::Done) {
            std::cout << "Error accept" << std::endl;
            return false;
        }

        std::cout << "new player connected" << std::endl;
        m_selector.add(m_clients[m_clientsCount]);
        m_clientsCount++;
        return true;
    } else {
        std::cout << "Error : maximum client limit" << std::endl;
    }
    return false;
}

void ServerTCPManager::receiveCommunication(int& index, std::vector<ServerPlayer*>& players) {
    std::cout << "[recv] ";
    sf::Packet packetNewPlayer;
    sf::TcpSocket::Status s = m_clients[index].receive(packetNewPlayer);

    if (s == sf::TcpSocket::Done) {
        sf::Uint8 req;
        packetNewPlayer >> req;

        if (req == REQ_NEW_PLAYER) {
            std::cout << "New Player info" << std::endl;
            std::string name;
            packetNewPlayer >> name;
            std::cout << "added new player : " << name << std::endl;
            players.push_back(new ServerPlayer(index, name, &m_clients[index]));
        } else if (req == REQ_ACK) {
            std::cout << "Ack" << std::endl;
            m_acknowledgment.release();
        } else {
            std::cout << "Undefined Request" << std::endl;
        }
    } else if (s == sf::TcpSocket::Disconnected) {
        std::cout << "player Disconnected" << std::endl;
        m_selector.remove(m_clients[index]);
        // @TODO remove from players too
        index--;
    } else if (s == sf::TcpSocket::Error) {
        std::cout << "Error Recv" << std::endl;
    } else {
        std::cout << "Error Invalide status : " << s << std::endl;
    }
}
