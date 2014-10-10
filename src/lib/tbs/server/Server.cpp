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
    map = new TileMap();

    generateMap(*map, 800, 600);

    // @TODO send map to client
    sf::Packet mapPacket = map->serialize();
    if (socket.send(mapPacket, client, port) != sf::Socket::Done) {
        // Erreur
    }
}

#include "../../../include/tbs/client/ValueNoise.h"

void Server::generateMap(TileMap& map, int imageWidth, int imageHeight) {
    float invImageWidth = 1.f / imageWidth, invImageHeight = 1.f / imageHeight;
    ValueNoise simpleNoise2D;
    float level[imageWidth * imageHeight];

    for (int j = 0; j < imageHeight; ++j) {
        for (int i = 0; i < imageWidth; ++i) {
            sf::Vector2f pnoise(i * invImageWidth, j * invImageHeight);
            pnoise.x *= 10.0f;
            pnoise.y *= 10.0f;
            float n = simpleNoise2D.Eval(pnoise);
            level[i + j * imageWidth] = n;
        }
    }

    map.load(sf::Vector2u(200, 200), level, imageWidth, imageHeight);
}
