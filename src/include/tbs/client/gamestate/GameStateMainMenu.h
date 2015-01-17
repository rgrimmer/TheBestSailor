#pragma once

#include <SFML/Network/IpAddress.hpp>

#include "GameState.h"
#include "client/ConnectionView.h"
#include "client/ChoiceIpView.h"

class ClientNetwork;
class ClientPlayer;

class GameStateMainMenu : public GameState {
public:

    enum EState {
        e_state_ip_choice,
        e_state_connection,
        e_state_send_info,
        e_state_recv_info,
        e_state_end
    };

    explicit GameStateMainMenu(sf::RenderWindow& window, ClientNetwork& network, ClientPlayer& player);
    virtual ~GameStateMainMenu(void);

    virtual void Initialize(void);
    virtual void Release(void);
    virtual void Activate(void);
    virtual void DeActivate(void);

    virtual void Update(float dt);
    virtual void Render(sf::RenderWindow& window);

    virtual bool read(sf::Event& event);
    virtual bool read(MsgData& msg);

private:
    void changeState(EState state);
    void initConnectionWithServer(const sf::IpAddress &address);
    void sendLocalPlayerInfo();
    void waitServerPlayerInfo();

    bool readMsgServerPlayerInfo(MsgData& msg);

    sf::Drawable* m_currentView;
    ChoiceIpView m_choiceIpView;
    ConnectionView m_connectionView;
    
    EState m_eState;
    unsigned short m_port;
    sf::IpAddress m_address;
    std::string m_ipAddressInput;

};