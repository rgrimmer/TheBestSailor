#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/System/Time.hpp>

class ClientNetwork;
class ClientPlayer;
class MsgData;

class State {
public:

    explicit State(void);
    virtual ~State(void);

    virtual void initialize(void) = 0;
    virtual void release(void) = 0;
    virtual void activate(void) = 0;
    virtual void deActivate(void) = 0;

    virtual void update(float dt) = 0;
    virtual void render(sf::RenderWindow& window) const = 0;
    
    virtual bool read(sf::Event& event) = 0;
    virtual bool read(MsgData& msg) = 0;
    
};