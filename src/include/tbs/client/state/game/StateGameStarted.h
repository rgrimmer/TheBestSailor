/* 
 * File:   StateGameStarted.h
 * Author: maxence
 *
 * Created on 18 janvier 2015, 15:54
 */

#ifndef STATEGAMESTARTED_H
#define	STATEGAMESTARTED_H

#include <bitset>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Audio/Music.hpp>

#include "client/state/State.h"

class GameStateManager;
class ClientNetwork;
class ClientPlayer;
class ClientWorld;
class DetailsView;
class GlobalView;

class StateGameStarted : public State {
public:
    StateGameStarted(GameStateManager& manager, ClientNetwork& network, ClientPlayer& player, ClientWorld& world);
    virtual ~StateGameStarted();

    virtual void initialize(void);
    virtual void release(void);
    virtual void activate(void);
    virtual void deactivate(void);
    virtual void update(float dt);
    virtual void render(sf::RenderWindow& window) const;
    virtual bool read(sf::Event& event);
    virtual bool read(MsgData& msg);

private:
    bool readGameInfo(MsgData& msg);
    bool readDisconnect(MsgData& msg);
    bool readCheckpoint(MsgData& msg);
    bool readMsgEnd(MsgData& msg);
    
    bool switchFollowingCamera();

private:
    GameStateManager& m_manager;
    ClientNetwork& m_network;
    ClientPlayer& m_player;
    ClientWorld& m_world;
    
    std::bitset<4> m_keys;
    bool m_followingCamera;
    float m_zoomValue;
    
    // Graphic
    sf::Drawable* m_mainGraphic;
    DetailsView* m_detailsView;
    GlobalView* m_globalView;
    
    // Sound
    sf::Music m_music;
};

#endif	/* STATEGAMESTARTED_H */

