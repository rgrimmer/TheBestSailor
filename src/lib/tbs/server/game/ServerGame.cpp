/* 
 * File:   ServerGame.cpp
 * Author: maxence
 * 
 * Created on 13 décembre 2014, 11:08
 */

#include <SFML/Network/Packet.hpp>

#include "shared/network/MessageData.h"

#include "server/ServerPlayer.h"
#include "server/ServerPlayers.h"
#include "server/Server.h"
#include "server/game/ServerGame.h"

ServerGame::ServerGame(Server& server, ServerPlayers& players)
: m_server(server)
, m_players(players)
, m_readerThread(nullptr) {
    m_players.putPlayersInGame();
}

ServerGame::~ServerGame() {
}

void ServerGame::start() {
    init();
    startReaderThread();
    
    // @TODO This is a test. Make update only when info send or after read message
    sf::Clock sendInfoClock;
    sf::Time minimunSendLimit = sf::seconds(1.0f / 30.0f);
    while (!gameIsEnded()) {
        sendInfoClock.restart();
        doUpdate();
        sendInfo();
        sf::sleep(minimunSendLimit - sendInfoClock.getElapsedTime());
    }
}

void ServerGame::startReaderThread() {
    delete m_readerThread;
    m_readerThread = new std::thread(&ServerGame::readerLoop, this);
}

void ServerGame::readerLoop() {
    // Wile game is not ended, we read messages. And check ended each 5s
    while (!gameIsEnded()) {
        // If we read somthing, we update world
        if (m_server.readMessagesWait(sf::milliseconds(5000))) {
            doUpdate();
        }
    }
}

void ServerGame::doUpdate() {
    // @TODO Si une update est en cour, attendre. 
    // Une fois fini, passer directement à la fin de la fonction, ne pas faire l'update
    // Verifier si sa ne pose pas de problème avec le read
    update(m_updateClock.restart().asSeconds());
}

