/* 
 * File:   ServerGame.cpp
 * Author: maxence
 * 
 * Created on 13 décembre 2014, 11:08
 */

#include <SFML/Network/Packet.hpp>

#include "shared/network/MsgData.h"

#include "server/ServerPlayer.h"
#include "server/ServerPlayers.h"
#include "server/Server.h"
#include "server/game/ServerGame.h"

ServerGame::ServerGame(Server& server, ServerPlayers& players)
: m_server(server)
, m_players(players) {
    m_players.putPlayersInGame();
}

ServerGame::~ServerGame() {
}

void ServerGame::start() {
    init();
    m_server.startReaderThread();
    
    // Make update only when info send or after read message
    sf::Clock sendInfoClock;
    sf::Time minimunSendLimit = sf::seconds(1.0f / 10.0f);
    while (!gameIsEnded()) {
        sendInfoClock.restart();
        doUpdate();
        sendInfo();
        sf::sleep(minimunSendLimit - sendInfoClock.getElapsedTime());
    }
    m_server.stopReaderThread();
}

void ServerGame::doUpdate() {
    // @TODO Si une update est en cours, attendre. 
    // Une fois fini, passer directement à la fin de la fonction, ne pas faire l'update
    // Verifier si sa ne pose pas de problème avec le read
    update(m_updateClock.restart().asSeconds());
}

