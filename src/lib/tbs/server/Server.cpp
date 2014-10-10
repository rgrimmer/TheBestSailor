/* 
 * File:   Server.cpp
 * Author: maxence
 * 
 * Created on 9 octobre 2014, 18:30
 */

#include "server/Server.h"

Server::Server() :
map(NULL) {
}

Server::Server(const Server& orig) {
}

Server::~Server() {
    delete map;
}

void Server::start(void) {
    sf::UdpSocket socket;
    sf::IpAddress client;
    unsigned short port;
    sf::Packet packet;

    // @TODO get a connection
    socket.receive(packet, client, port);
    // @TODO generate a map
    map = new Map();

    map->generate(800, 600);

    // @TODO send map to client
    sf::Packet mapPacket;
    if (socket.send(mapPacket << map, client, port) != sf::Socket::Done) {
        // Erreur
    }
}