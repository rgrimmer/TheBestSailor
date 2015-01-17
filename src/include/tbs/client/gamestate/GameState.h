#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/System/Time.hpp>

#include "client/network/ClientNetwork.h"
#include "client/ClientPlayer.h"

class ClientNetwork;
class ClientPlayer;
class MsgData;

class GameState {
public:
    enum EGameState {
        e_game_state_main_menu,
        e_game_state_game,
        e_game_state_max
    };

    explicit GameState(sf::RenderWindow& window, ClientNetwork& network, ClientPlayer& player);
    virtual ~GameState(void);

    virtual void Initialize(void) = 0;
    virtual void Release(void) = 0;
    virtual void Activate(void) = 0;
    virtual void DeActivate(void) = 0;

    virtual void Update(float dt) = 0;
    virtual void Render(sf::RenderWindow& window) = 0;
    
    virtual bool read(sf::Event& event) = 0;
    virtual bool read(MsgData& msg) = 0;
  
    void pollMessages();
    bool pollMessagesWait(sf::Time timeout = sf::Time::Zero);
    
protected:
    sf::RenderWindow& m_window;
    ClientNetwork& m_network;
    ClientPlayer& m_player;
};