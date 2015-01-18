
#include "client/state/mainMenu/StateMainMenu.h"

StateMainMenu::StateMainMenu(ClientState& manager, ClientNetwork& network, ClientPlayer& player)
: m_states(manager, network, player) {
}

StateMainMenu::~StateMainMenu(void) {

}

void StateMainMenu::initialize(void) {
    m_states.initialize();
}

void StateMainMenu::release(void) {
    m_states.release();
}

void StateMainMenu::activate(void) {
    m_states.activate();
}

void StateMainMenu::deactivate(void) {
    m_states.deactivate();
}

void StateMainMenu::update(float dt) {
    m_states.update(dt);
}

void StateMainMenu::render(sf::RenderWindow& window) const {
    m_states.render(window);
}

bool StateMainMenu::read(sf::Event& event) {
    return m_states.read(event);
}

bool StateMainMenu::read(MsgData& msg) {
    return m_states.read(msg);
}