/* 
 * File:   MainMenuStateManager.cpp
 * Author: maxence
 * 
 * Created on 18 janvier 2015, 10:44
 */

#include "client/state/mainMenu/MainMenuStateManager.h"
#include "client/state/mainMenu/StateMainMenuChoiceIp.h"
#include "client/state/mainMenu/StateMainMenuExchangeInfo.h"

MainMenuStateManager::MainMenuStateManager(ClientState& manager, ClientNetwork& network, ClientPlayer& player)
: m_manager(manager)
, m_network(network)
, m_player(player) {
}

MainMenuStateManager::~MainMenuStateManager() {
}

void MainMenuStateManager::initialize() {
    add(EMainMenuState::ChoiceIp, new StateMainMenuChoiceIp(*this, m_address));
    add(EMainMenuState::SendInfo, new StateMainMenuExchangeInfo(*this, m_network, m_player, m_address));
    
    m_apState[EMainMenuState::ChoiceIp]->initialize();
    m_apState[EMainMenuState::SendInfo]->initialize();

    push(EMainMenuState::ChoiceIp);
}

ClientState& MainMenuStateManager::getClientManager() {
    return m_manager;
}
