#include "client/network/ClientNetwork.h"
#include "client/ClientPlayer.h"

#include "client/state/State.h"

State::State(void) {

}

State::~State(void) {

}
/*
void State::pollMessages() {
    while (!m_network.getMessageQueue().empty()) {
        auto message = m_network.getMessageQueue().pop();
        if(!read(*message))
            break;
    }
}

bool State::pollMessagesWait(sf::Time timeout) {
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
*/