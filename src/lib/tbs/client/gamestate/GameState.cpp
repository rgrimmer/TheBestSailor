#include "client/gamestate/GameState.h"

GameState::GameState(void) {

}

GameState::~GameState(void) {

}
void GameState::pollMessages() {
    while (!m_network->getMessageQueue().empty()) {
        auto message = m_network->getMessageQueue().pop();
        read(*message);
    }
}

bool GameState::pollMessagesWait(sf::Time timeout) {
    if (m_network->getMessageQueue().empty()) {
        std::cout << "[Client][PoolM][Wait]" << std::endl;
        if (!m_network->getMessageQueue().waitEvent(timeout)) {
            std::cout << "[Client][PoolM][Wait] \t timeout" << std::endl;
            return false;
        }
    }
    pollMessages();
    return true;
}