/* 
 * File:   Server.cpp
 * Author: maxence
 * 
 * Created on 9 octobre 2014, 18:30
 */

#include <iostream>
#include <unistd.h>
#include <vector>
#include <ctime>

#include "server/Server.h"
#include "shared/Utils.h"

/*sf::Packet& operator<<(sf::Packet &packet, const MapHeader &header) {
    int mapWidth = header.getWidth();
    int mapHeight = header.getHeight();
    int mapSeed = header.getSeed();

    // @TODO check syntaxe of cast
    packet << (sf::Int32) mapWidth
            << (sf::Int32) mapHeight
            << (sf::Int32) mapSeed
            ;
    return packet;
}*/

Server::Server() {
}

Server::~Server() {

}

void Server::start() {
    srand(time(NULL));
    m_clientsCount = 0;
    m_world.initialize();
    waitConnections();
}

void Server::waitConnections() {
    sf::SocketSelector selector;
    sf::TcpListener listener;
    bool stay = true;
    
    // bind the listener to a port
    if (listener.listen(SERVER_PORT) != sf::Socket::Done) {
        std::cout << "Error listen" << std::endl;
        return;
    }

    selector.add(listener);
    
    while (stay) {
        stay = false;
        
        if (selector.wait(sf::seconds(5.0f))) {
            stay = true;
            for (int i = 0; i < m_clientsCount; ++i) {

                if (selector.isReady(m_clients[i])) {
                    sf::Packet packetRecv;
                    sf::TcpSocket::Status s = m_clients[i].receive(packetRecv);
                    sf::Packet packet = m_world.getMapPacket();
                    
                    if (s == sf::TcpSocket::Disconnected) {
                        std::cout << "player disconnected" << std::endl;
                        selector.remove(m_clients[i]);
                    }
                    else if (s == sf::TcpSocket::Error) {
                        std::cout << "Error recv" << std::endl;
                        return;
                    }
                    else {
                        m_clients[i].send(packet);
                    }
                }
            }

            if (m_clientsCount < NB_CLIENT_MAX && selector.isReady(listener)) {
                if (listener.accept(m_clients[m_clientsCount]) != sf::Socket::Done) {
                    std::cout << "Error accept" << std::endl;
                    return;
                }

                std::cout << "new player connected" << std::endl;
                selector.add(m_clients[m_clientsCount]);
                m_clientsCount++;
            }
        }
           
    }
    listener.close();
    for(int i=0 ; i < m_clientsCount ; ++i) {
        m_clients[i].disconnect();
    }

}