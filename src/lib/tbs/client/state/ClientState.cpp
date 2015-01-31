/* 
 * File:   ClientState.cpp
 * Author: maxence
 * 
 * Created on 17 janvier 2015, 17:36
 */

#include "client/state/ClientState.h"
#include "client/state/mainMenu/ClientStateMenu.h"
#include "client/state/game/ClientStateGame.h"

ClientState::ClientState(ClientNetwork& network, ClientPlayer& player)
: m_network(network)
, m_player(player) {
}

ClientState::~ClientState() {
}

EClientState ClientState::firstState() const {
    return EClientState::MainMenu;
}

void ClientState::create(EClientState estate) {
    switch (estate) {
        case EClientState::Game:
            add(EClientState::Game, new ClientStateGame(*this, m_network, m_player));
            break;
        case EClientState::MainMenu:
            add(EClientState::MainMenu, new ClientStateMenu(*this, m_network, m_player));
            break;
    }
}
