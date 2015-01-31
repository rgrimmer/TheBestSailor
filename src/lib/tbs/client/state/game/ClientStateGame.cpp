
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

void ClientStateGame::create(EStateGame eState) {
    switch (eState) {
        case EStateGame::Wait:
            add(eState, new ClientStateGameWait(*this, m_network, m_player, m_world));
            break;
        case EStateGame::Started:
            add(eState, new ClientStateGameStarted(*this, m_network, m_player, m_world));
            break;
        case EStateGame::End:
            add(eState, new ClientStateGameEnd(*this, m_network, m_player, m_world));
            break;
    }
}

void ClientStateGame::deactivate() {
    std::cout << "[StateGame][Desactivate]" << std::endl;
    m_network.getTcpManager().disconnect();
}

EStateGame ClientStateGame::firstState() const {
    return EStateGame::Wait;
}

