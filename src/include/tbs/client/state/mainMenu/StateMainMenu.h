#pragma once

#include "client/state/State.h"
#include "client/state/mainMenu/ClientStateMenu.h"

class ClientState;
class ClientNetwork;
class ClientPlayer;

class StateMainMenu : public State {
public:
    explicit StateMainMenu(ClientState& manager, ClientNetwork& network, ClientPlayer& player);
    virtual ~StateMainMenu(void);

    virtual void initialize(void);
    virtual void release(void);
    virtual void activate(void);
    virtual void deactivate(void);
    virtual void update(float dt);
    virtual void render(sf::RenderWindow& window) const;
    virtual bool read(sf::Event& event);
    virtual bool read(MsgData& msg);
    
private:
    ClientStateMenu m_states;
};


