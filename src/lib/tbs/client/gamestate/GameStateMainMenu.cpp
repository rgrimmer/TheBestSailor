#include <stdio.h>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include "shared/network/UtilsNetwork.h"
#include "shared/network/MsgData.h"

#include "client/gamestate/GameStateMainMenu.h"
#include "client/gamestate/GameStateManager.h"
#include "client/ClientPlayer.h"
#include "client/network/ClientNetwork.h"

GameStateMainMenu::GameStateMainMenu()
: GameState()
, m_view(m_ipAddressInput) {

}

GameStateMainMenu::~GameStateMainMenu(void) {

}

void GameStateMainMenu::Initialize(ClientNetwork& network, ClientPlayer& player) {
    m_network = &network;
    m_player = &player;
    m_port = SERVER_PORT_TCP;
    m_address = sf::IpAddress::None;
    m_ipAddressInput = "localhost";
}

void GameStateMainMenu::Release(void) {

}

void GameStateMainMenu::Activate(void) {
    m_eState = e_state_ip_choice;
}

void GameStateMainMenu::DeActivate(void) {

}

void GameStateMainMenu::Update(float deltaTimeInMs) {
    switch (m_eState) {

        case e_state_connection:
        {
            /*
            while (m_window.isOpen()) {
                initGame();
                startGame();
            }
            doDisconnection();*/

        }
            break;

        case e_state_ip_choice:
        {

        }
            break;

        default:
            break;

    }
}

void GameStateMainMenu::Render(sf::RenderWindow & window) {
    window.draw(m_view);
}

bool GameStateMainMenu::read(sf::Event& event) {

    if (event.type == sf::Event::TextEntered) {
        char c = static_cast<char> (event.text.unicode);
        //        std::cout << "Text entred(" << c << ")" << std::endl;
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '.') {
            m_ipAddressInput.append(&c, 1);
        }
    } else if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::BackSpace && m_ipAddressInput.size() > 0) {
            m_ipAddressInput.resize(m_ipAddressInput.size() - 1);
        }
        if (event.key.code == sf::Keyboard::Return) {
            m_address = sf::IpAddress(m_ipAddressInput);
            m_eState = e_state_connection;
            changeState(e_state_connection);
        }
    } else if (event.type == sf::Event::Closed) {
        return false;
    }

    return true;
}

void GameStateMainMenu::initConnectionWithServer(const sf::IpAddress &address) {
    std::cout << "[NetW][InitCWS]\tInitialize connection" << std::endl;
    m_network->connect(address);
    m_network->getTcpManager().startReceiverThread();
    sendLocalPlayerInfo();
    waitServerPlayerInfo();
}

void GameStateMainMenu::changeState(EState state) {

    m_eState = state;

    if (m_eState == e_state_connection) {
        std::cout << "TRY TO CONNECT TO " << m_address.toString() << std::endl;
        initConnectionWithServer(m_address);
    }
}

void GameStateMainMenu::sendLocalPlayerInfo() {
    std::cout << "[Client][SendLPI] \t Envoi des informations du joueurs" << std::endl;
    MsgData msg;
    msg << MsgType::ClientPlayerInfo << static_cast<sf::Uint16> (m_network->getUdpManager().getPort()) << m_player->getName();
    m_network->getTcpManager().send(msg);
    std::cout << "[Client][SendLPI] \t Send : name(" << m_player->getName() << ") port(" << m_network->getUdpManager().getPort() << ")" << std::endl;
}

void GameStateMainMenu::waitServerPlayerInfo() {
    std::cout << "[Client][WSPI] \t Wait information from server" << std::endl;
    pollMessagesWait(sf::Time::Zero);
}

void Client::pollMessages() {
    while (!m_network.getMessageQueue().empty()) {
        auto message = m_network.getMessageQueue().pop();
        read(*message);
    }
}

bool Client::pollMessagesWait(sf::Time timeout) {
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