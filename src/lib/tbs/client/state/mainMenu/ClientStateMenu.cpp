/* 
 * File:   ClientStateMenu.cpp
 * Author: maxence
 * 
 * Created on 18 janvier 2015, 10:44
 */

#include "client/state/mainMenu/ClientStateMenu.h"
#include "client/state/mainMenu/ClientStateMenuChoiceIp.h"
#include "client/state/mainMenu/ClientStateMenuExchangeInfo.h"

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

void ClientStateMenu::initialize() {
    add(EMainMenuState::ChoiceIp, new ClientStateMenuChoiceIp(*this, m_address));
    add(EMainMenuState::SendInfo, new ClientStateMenuExchangeInfo(*this, m_network, m_player, m_address));
    
    m_apState[EMainMenuState::ChoiceIp]->initialize();
    m_apState[EMainMenuState::SendInfo]->initialize();

    push(EMainMenuState::ChoiceIp);
}

