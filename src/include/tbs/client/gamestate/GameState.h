#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

class ClientNetwork;
class ClientPlayer;

class GameState {
public:

    explicit GameState(void);
    virtual ~GameState(void);

    virtual void Initialize(ClientNetwork& network, ClientPlayer& player) = 0;
    virtual void Release(void) = 0;
    virtual void Activate(void) = 0;
    virtual void DeActivate(void) = 0;

    virtual void Update(float dt) = 0;
    virtual void Render(sf::RenderWindow & window) = 0;
    
    virtual bool read(sf::Event& event) = 0;
    
protected:
    ClientNetwork* m_network;
};