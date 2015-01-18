/* 
 * File:   ClientState.cpp
 * Author: maxence
 * 
 * Created on 17 janvier 2015, 17:36
 */

#include "client/state/ClientState.h"
#include "client/state/mainMenu/StateMainMenu.h"
#include "client/state/game/StateGame.h"

ClientState::ClientState(ClientNetwork& network, ClientPlayer& player)
: m_network(network)
, m_player(player) {
}

ClientState::~ClientState() {
}

void ClientState::initialize() {

    add(EClientState::MainMenu, new StateMainMenu(*this, m_network, m_player));
    add(EClientState::Game, new StateGame(*this, m_network, m_player));

    m_apState[EClientState::MainMenu]->initialize();
    m_apState[EClientState::Game]->initialize();

    push(EClientState::MainMenu);
}

