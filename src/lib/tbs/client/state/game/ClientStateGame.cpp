
#include "client/network/ClientNetwork.h"

#include "client/state/game/ClientStateGame.h"
#include "client/state/game/ClientStateGameWait.h"
#include "client/state/game/ClientStateGameStarted.h"
#include "client/state/game/ClientStateGameEnd.h"

ClientStateGame::ClientStateGame(ClientState& manager, ClientNetwork& network, ClientPlayer& player)
: m_manager(manager)
, m_network(network)
, m_player(player)
, m_world() {
}

ClientStateGame::~ClientStateGame(void) {

}

ClientState& ClientStateGame::getManager() {
    return m_manager;
}

void ClientStateGame::initialize(void) {
    add(EStateGame::Wait, new ClientStateGameWait(*this, m_network, m_player, m_world));
    add(EStateGame::Started, new ClientStateGameStarted(*this, m_network, m_player, m_world));
    add(EStateGame::End, new ClientStateGameEnd(*this, m_network, m_player, m_world));
    
    m_apState[EStateGame::Wait]->initialize();
    m_apState[EStateGame::Started]->initialize();

    push(EStateGame::Wait);
}

void ClientStateGame::deactivate() {
    std::cout << "[StateGame][Desactivate]" << std::endl;
    m_network.getTcpManager().disconnect();
}

