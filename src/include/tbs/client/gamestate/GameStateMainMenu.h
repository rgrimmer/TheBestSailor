#pragma once

#include <SFML/Network/IpAddress.hpp>

#include "GameState.h"
#include "client/ConnectionView.h"

class ClientNetwork;
class ClientPlayer;

class GameStateMainMenu : public GameState {
public:

    enum EState {
        e_state_ip_choice,
        e_state_connection
    };

    explicit GameStateMainMenu(void);
    virtual ~GameStateMainMenu(void);

    virtual void Initialize(ClientNetwork& network, ClientPlayer& player);
    virtual void Release(void);
    virtual void Activate(void);
    virtual void DeActivate(void);

    virtual void Update(float dt);
    virtual void Render(sf::RenderWindow & window);

    virtual bool read(sf::Event& event);

private:
    void changeState(EState state);
    void initConnectionWithServer(const sf::IpAddress &address);
    void sendLocalPlayerInfo();
    void waitServerPlayerInfo();


    ConnectionView m_view;
    ClientNetwork* m_network;
    ClientPlayer* m_player;
    EState m_eState;
    unsigned short m_port;
    sf::IpAddress m_address;
    std::string m_ipAddressInput;

};