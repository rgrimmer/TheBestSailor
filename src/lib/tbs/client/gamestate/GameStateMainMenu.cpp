#include <stdio.h>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include "shared/network/UtilsNetwork.h"
#include "shared/network/MsgData.h"

#include "client/gamestate/GameStateMainMenu.h"
#include "client/gamestate/GameStateManager.h"
#include "client/ClientPlayer.h"
#include "client/network/ClientNetwork.h"
#include "shared/network/MsgTurnHelm.h"

GameStateMainMenu::GameStateMainMenu(ClientNetwork& network, ClientPlayer& player)
: GameState(network, player)
, m_choiceIpView(m_ipAddressInput)
, m_connectionView(m_ipAddressInput) {

}

GameStateMainMenu::~GameStateMainMenu(void) {

}

void GameStateMainMenu::Initialize(void) {
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

}

void GameStateMainMenu::Render(sf::RenderWindow & window) {
    switch (m_eState) {

        case e_state_ip_choice:
        {
            window.draw(m_choiceIpView);
        }
            break;
            
        case e_state_connection:
        {
            window.draw(m_connectionView);
        }
            break;

        default:
            break;

    }
}

void GameStateMainMenu::initConnectionWithServer(const sf::IpAddress &address) {
    std::cout << "[NetW][InitCWS]\tInitialize connection" << std::endl;
    m_network.connect(address);
    m_network.getTcpManager().startReceiverThread();
    sendLocalPlayerInfo();
    waitServerPlayerInfo();
}

void GameStateMainMenu::changeState(EState state) {

    m_eState = state;

    if (m_eState == e_state_connection) {
//        std::cout << "TRY TO CONNECT TO " << m_address.toString() << std::endl;
//        initConnectionWithServer(m_address);
    }
}

void GameStateMainMenu::sendLocalPlayerInfo() {
    std::cout << "[Client][SendLPI] \t Envoi des informations du joueurs" << std::endl;
    MsgData msg;
    msg << MsgType::ClientPlayerInfo << static_cast<sf::Uint16> (m_network.getUdpManager().getPort()) << m_player.getName();
    m_network.getTcpManager().send(msg);
    std::cout << "[Client][SendLPI] \t Send : name(" << m_player.getName() << ") port(" << m_network.getUdpManager().getPort() << ")" << std::endl;
}

void GameStateMainMenu::waitServerPlayerInfo() {
    std::cout << "[Client][WSPI] \t Wait information from server" << std::endl;
    pollMessagesWait(sf::Time::Zero);
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
        } else if (event.key.code == sf::Keyboard::Return) {
            m_address = sf::IpAddress(m_ipAddressInput);
            changeState(e_state_connection);
        } else if (event.key.code == sf::Keyboard::Escape) {
            if(m_eState == e_state_ip_choice) 
                return false;
            changeState(e_state_ip_choice);
        }
    } else if (event.type == sf::Event::Closed) {
        return false;
    }

    return true;
}

bool GameStateMainMenu::read(MsgData& msg) {
    MsgType msgType;
    msg >> msgType;
    switch (msgType) {
            //        case MsgType::Game:
            //            return readMsgGame(msg);
        case MsgType::ServerPlayerInfo:
            return readMsgServerPlayerInfo(msg);
    }
    return true;
}

bool GameStateMainMenu::readMsgServerPlayerInfo(MsgData &message) {
    sf::Uint16 udpPort, id;
    message >> udpPort >> id;
    std::cout << "[Client][Read] \t Read Server Player Info Message. id(" << id << "), serverUdpPort(" << udpPort << ")" << std::endl;
    m_player.setId(id);
    m_network.getUdpManager().initialize(m_address, udpPort);
    m_network.getUdpManager().startReceiverThread();
    //    g_gameStateManager.Push(/*game*/);
    return true;
}