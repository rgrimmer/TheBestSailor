#include <iostream>

#include <server/network/ServerUDPManager.h>

#include <shared/Utils.h>
#include <shared/network/Request.h>

ServerUDPManager::ServerUDPManager() {

}

ServerUDPManager::~ServerUDPManager() {

}

bool ServerUDPManager::initialize(unsigned short port) {
    m_port = port;

    sf::Socket::Status status = m_socket.bind(m_port);
    return status == sf::Socket::Done;
}

bool ServerUDPManager::send(sf::Packet packet, const sf::IpAddress & address, unsigned short port) {
    sf::Socket::Status status = m_socket.send(packet, address, port);
    return (status == sf::Socket::Done);
}

bool ServerUDPManager::receiveIdentifyRequests(std::vector<ServerPlayer*> players) {
    unsigned int requestCount = 0;

    while (requestCount < players.size()) {
        sf::Packet packet;
        sf::IpAddress senderAddress;
        unsigned short senderPort;

        if (m_socket.receive(packet, senderAddress, senderPort) != sf::Socket::Done) {
            return false;
        }


        sf::Uint8 id=0;
        packet >> id;
        
        std::cout << "PORT : " << senderPort << "ID : " << static_cast<int>(id) << std::endl;
        
        ServerPlayer* player = nullptr;

        for (ServerPlayer* p : players) {
            if (p->getId() == id) {
                player = p;
                break;
            }
        }

        if (player != nullptr) {
            player->setUdpPort(senderPort);
        } else {
            return false;
        }

        requestCount++;
    }

    return true;
}

sf::Packet ServerUDPManager::receive() {
    sf::Packet packet;
    sf::IpAddress senderAddress;
    unsigned short senderPort;

    if (m_socket.receive(packet, senderAddress, senderPort) != sf::Socket::Done) {
        sf::Packet errorPacket;
        errorPacket << -1;
        return errorPacket;
    }

    return packet;

    /*if (m_socket.receive(packet, senderAddress, senderPort) != sf::Socket::Done) {
        return packet;
    }

    sf::Packet resp;

    sf::Uint8 req;
    packet >> req;

    switch (req) {
        case REQ_IDENT:
        {
            resp << senderPort;
            break;
        }
        case REQ_ACTION_TURN_HELM:
        {
            std::cout << "REQ_ACTION_TURN_HELM" << std::endl;
            resp << 1;
        }
            break;
        default: // Error
            return packet;
    }

    return resp;*/
}
