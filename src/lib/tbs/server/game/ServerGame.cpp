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
, m_players(players) {
    m_players.putPlayersInGame();
}

ServerGame::~ServerGame() {
}

void ServerGame::start() {
    initGame();
    startGameLoop();
}
