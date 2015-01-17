/* 
 * File:   ClientState.cpp
 * Author: maxence
 * 
 * Created on 17 janvier 2015, 17:36
 */

#include "client/state/ClientState.h"
#include "client/state/StateMainMenu.h"
#include "client/state/StateGame.h"

ClientState::ClientState(ClientNetwork& network, ClientPlayer& player)
: m_network(network)
, m_player(player) {
}

ClientState::~ClientState() {
}

void ClientState::initialize() {

    add(EClientState::e_game_state_main_menu, new StateMainMenu(*this, m_network, m_player));
    add(EClientState::e_game_state_game, new StateGame(*this, m_network, m_player));

    m_apState[EClientState::e_game_state_main_menu]->initialize();
//    m_apState[GameState::EGameState::e_game_state_game]->Initialize();

    m_eCurrentState = EClientState::e_game_state_main_menu;
    push(m_eCurrentState);
}

