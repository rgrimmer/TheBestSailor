/* 
 * File:   ServerGameSpeedestWin.cpp
 * Author: maxence
 * 
 * Created on 13 décembre 2014, 11:19
 */
#include <iostream>

#include "shared/network/Message.h"
#include "shared/network/MsgTurnHelm.h"
#include "shared/network/MsgTurnSail.h"
#include "shared/network/MsgDisconnect.h"

#include "server/Server.h"
#include "server/game/ServerGameSpeedestWin.h"

sf::Packet& operator<<(sf::Packet& packet, const ServerGameSpeedestWin& game) {
    return packet << game.getMap();
}

ServerGameSpeedestWin::ServerGameSpeedestWin(Server &server, PlayerList& players, const MapHeader &header)
: ServerGame(server, players)
, m_map(header) {
}

ServerGameSpeedestWin::~ServerGameSpeedestWin() {
}

const Map& ServerGameSpeedestWin::getMap() const {
    return m_map;
}

void ServerGameSpeedestWin::initGame() {
    //send player list to others
//    sf::Packet packetPlayerList;

//    packetPlayerList << static_cast<sf::Uint8> (m_players.size());
//
//    for (const auto p : m_players.inGame()) {
//        packetPlayerList << static_cast<sf::Uint8> (p->getId());
//        packetPlayerList << p->getName();
//    }
//
//    std::cout << "send players list to all players.........." << std::endl;
//    for (const auto p : m_players.inGame()) {
//        m_server.m_network.getTCPManager().send(packetPlayerList, p->getTCPSocket());
//    }
}

void ServerGameSpeedestWin::startGameLoop() {
    bool hasWinner = false;
    sf::Clock clockUpdate;
    sf::Time updateRate = sf::milliseconds(2);

    // @TODO start sender game state thread

    do {
        // Poll event
        m_server.pollMessages();

        // @TODO Update entities
        //        m_world.update();

        // @TODO Check if someone win

        // Limit the update rate
        sf::sleep(clockUpdate.getElapsedTime() - updateRate);
        clockUpdate.restart();

    } while (!hasWinner);
}

sf::Packet ServerGameSpeedestWin::toPacket(sf::Packet &packet) const {
    return packet << m_map;
}

bool ServerGameSpeedestWin::read(MessageData* message, ServerPlayer* player) {
    switch (message->getType()) {
        case MSG_ACTION_TURN_HELM:
        {
            std::cout << "Turn Helm ";
            auto msg = dynamic_cast<MsgTurnHelm*> (message);

            if (msg->getOrientation() == msgOrientation::POSITIVE)
                std::cout << "POSITIVE";
            else if (msg->getOrientation() == msgOrientation::NEGATIVE)
                std::cout << "NEGATIVE";
            else
                std::cout << "ORIENTATION UNDEFINED (WARNING)";
        }
            break;
        case MSG_ACTION_TURN_SAIL:
        {
            std::cout << "Turn Sail ";
            auto msg = dynamic_cast<MsgTurnSail*> (message);

            if (msg->getOrientation() == msgOrientation::POSITIVE)
                std::cout << "POSITIVE";
            else if (msg->getOrientation() == msgOrientation::NEGATIVE)
                std::cout << "NEGATIVE";
            else
                std::cout << "UNDEFINED (WARNING)";
        }
            break;
        default:
            return false;
    }
    return true;
    std::cout << std::endl;
}

/*
    sf::Packet packetResponse;
    packetResponse << 0;

    for (ServerPlayer* p : m_playerList) {
        std::cout << "[send] resp to : " << p->getName() << " port = " << p->getUdpPort() << std::endl;
        m_network.getUDPManager().send(packetResponse, p->getAddress(), p->getUdpPort());
    }
 */
