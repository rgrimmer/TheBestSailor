#pragma once

#include <SFML/Network/IpAddress.hpp>

#include "client/state/State.h"
#include "client/state/ClientState.h"
#include "client/ConnectionView.h"
#include "client/ChoiceIpView.h"

class ClientState;
class ClientNetwork;
class ClientPlayer;

class StateMainMenu : public State {
public:

    enum EEState {
        e_state_ip_choice,
        e_state_connection,
        e_state_send_info,
        e_state_recv_info,
        e_state_end
    };

    explicit StateMainMenu(ClientState& manager, ClientNetwork& network, ClientPlayer& player);
    virtual ~StateMainMenu(void);

    virtual void initialize(void);
    virtual void release(void);
    virtual void activate(void);
    virtual void deActivate(void);

    virtual void update(float dt);
    virtual void render(sf::RenderWindow& window) const;

    virtual bool read(sf::Event& event);
    virtual bool read(MsgData& msg);

private:
    void changeState(EEState state);
    void initConnectionWithServer(const sf::IpAddress &address);
    void sendLocalPlayerInfo();

    bool readMsgServerPlayerInfo(MsgData& msg);
    
private:
    StateManager<EClientState>& m_manager;
    ClientNetwork& m_network;
    ClientPlayer& m_player;

    sf::Drawable* m_currentView;
    ChoiceIpView m_choiceIpView;
    ConnectionView m_connectionView;
    
    EEState m_eState;
    unsigned short m_port;
    sf::IpAddress m_address;
    std::string m_ipAddressInput;

};


