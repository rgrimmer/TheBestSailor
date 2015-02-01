/* 
 * File:   ClientStateMenu.cpp
 * Author: maxence
 * 
 * Created on 18 janvier 2015, 10:44
 */

#include <iostream>

#include "client/state/mainMenu/ClientStateMenu.h"
#include "client/state/mainMenu/ClientStateMenuChoiceIp.h"
#include "client/state/mainMenu/ClientStateMenuExchangeInfo.h"
#include "client/network/ClientNetwork.h"

ClientStateMenu::ClientStateMenu(ClientState& manager, ClientNetwork& network, ClientPlayer& player)
: m_manager(manager)
, m_network(network)
, m_player(player)
, m_address() {
}

ClientStateMenu::~ClientStateMenu() {
}

ClientState& ClientStateMenu::getManager() {
    return m_manager;
}

void ClientStateMenu::activate() {
    std::cout << "[ClientStateMenu][Activate]" << std::endl;
    m_network.disconnect();
    StateManager::activate();
}

void ClientStateMenu::create(EMainMenuState eState) {
    switch (eState) {
        case EMainMenuState::ChoiceIp:
            add(eState, new ClientStateMenuChoiceIp(*this, m_address));
            break;
        case EMainMenuState::ExchangeInfo:
            add(eState, new ClientStateMenuExchangeInfo(*this, m_network, m_player, m_address));
            break;
    }
}

EMainMenuState ClientStateMenu::firstState() const {
    return EMainMenuState::ChoiceIp;
}
