#include "client/network/ClientNetwork.h"
#include "client/ClientPlayer.h"

#include "client/gamestate/GameState.h"

GameState::GameState(sf::RenderWindow& window, ClientNetwork& network, ClientPlayer& player)
: m_window(window)
, m_network(network)
, m_player(player) {

}

GameState::~GameState(void) {

}

void GameState::pollMessages() {
    while (!m_network.getMessageQueue().empty()) {
        auto message = m_network.getMessageQueue().pop();
        if(!read(*message))
            break;
    }
}

bool GameState::pollMessagesWait(sf::Time timeout) {
    if (m_network.getMessageQueue().empty()) {
        std::cout << "[Client][PoolM][Wait]" << std::endl;
        if (!m_network.getMessageQueue().waitEvent(timeout)) {
            std::cout << "[Client][PoolM][Wait] \t timeout" << std::endl;
            return false;
        }
    }
    pollMessages();
    return true;
}
