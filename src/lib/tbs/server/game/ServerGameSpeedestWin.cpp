/* 
 * File:   ServerGameSpeedestWin.cpp
 * Author: maxence
 * 
 * Created on 13 décembre 2014, 11:19
 */
#include <iostream>

#include <SFML/System/Clock.hpp>
#include <SFML/System/Sleep.hpp>

#include "shared/network/MsgTurnHelm.h"
#include "shared/network/MsgTurnSail.h"
#include "shared/network/MsgDisconnect.h"
#include "shared/network/MessageData.h"

#include "server/Server.h"
#include "server/game/ServerGameSpeedestWin.h"

sf::Packet& operator<<(sf::Packet& packet, const ServerGameSpeedestWin& game) {
    return packet << game.getMap();
}

ServerGameSpeedestWin::ServerGameSpeedestWin(Server &server, ServerPlayers& players, const MapHeader &header)
: ServerGame(server, players)
, m_map(header) {
}

ServerGameSpeedestWin::~ServerGameSpeedestWin() {
}

const Map& ServerGameSpeedestWin::getMap() const {
    return m_map;
}

void ServerGameSpeedestWin::initGame() {
    // @TODO
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
    switch (message->getMsgType()) {
        case MsgType::ActionTurnHelm:
        {
            std::cout << "Turn Helm ";
            auto msg = dynamic_cast<MsgTurnHelm*> (message);
            sf::Int8 sfOrientation;
            *msg >> sfOrientation;
            MsgOrientation orientation = static_cast<MsgOrientation> (sfOrientation);
            if (orientation == MsgOrientation::POSITIVE)
                std::cout << "POSITIVE";
            else if (orientation == MsgOrientation::NEGATIVE)
                std::cout << "NEGATIVE";
            else
                std::cout << "UNDEFINED (WARNING)";
        }
            break;
        case MsgType::ActionTurnSail:
        {
            std::cout << "Turn Sail ";
            auto msg = dynamic_cast<MsgTurnSail*> (message);
            sf::Int8 sfOrientation;
            *msg >> sfOrientation;
            MsgOrientation orientation = static_cast<MsgOrientation> (sfOrientation);
            if (orientation == MsgOrientation::POSITIVE)
                std::cout << "POSITIVE";
            else if (orientation == MsgOrientation::NEGATIVE)
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
    // @TODO delete message, use unique_ptr ?
}

/*
    sf::Packet packetResponse;
    packetResponse << 0;

    for (ServerPlayer* p : m_players) {
        std::cout << "[send] resp to : " << p->getName() << " port = " << p->getUdpPort() << std::endl;
        m_network.getUDPManager().send(packetResponse, p->getAddress(), p->getUdpPort());
    }
 */
