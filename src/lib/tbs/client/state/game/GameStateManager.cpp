/* 
 * File:   GameStateManager.cpp
 * Author: maxence
 * 
 * Created on 18 janvier 2015, 17:18
 */

#include "client/state/ClientState.h"
#include "client/state/game/StateGameWait.h"
#include "client/state/game/StateGameStarted.h"
#include "client/state/game/GameStateManager.h"

GameStateManager::GameStateManager(ClientState& manager, ClientNetwork& network, ClientPlayer& player)
: m_manager(manager)
, m_network(network)
, m_player(player)
, m_world() {

}

GameStateManager::~GameStateManager() {
}

ClientState& GameStateManager::getManager() {
    return m_manager;
}

void GameStateManager::initialize() {
    add(EGameStateManager::Wait, new StateGameWait(*this, m_network, m_player, m_world));
    add(EGameStateManager::Started, new StateGameStarted(*this, m_network, m_player, m_world));
    
    m_apState[EGameStateManager::Wait]->initialize();
    m_apState[EGameStateManager::Started]->initialize();

    push(EGameStateManager::Wait);
}
