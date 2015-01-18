
#include "client/state/game/StateGame.h"

StateGame::StateGame(ClientState& manager, ClientNetwork& network, ClientPlayer& player)
: m_states(manager, network, player) {
}

StateGame::~StateGame(void) {

}

void StateGame::initialize(void) {
    m_states.initialize();
}

void StateGame::release(void) {
    m_states.release();
}

void StateGame::activate(void) {
    m_states.activate();
}

void StateGame::deactivate(void) {
    m_states.deactivate();
}

void StateGame::update(float dt) {
    m_states.update(dt);
}

void StateGame::render(sf::RenderWindow& window) const {
    m_states.render(window);
}

bool StateGame::read(sf::Event& event) {
    return m_states.read(event);
}

bool StateGame::read(MsgData& msg) {
    return m_states.read(msg);
}