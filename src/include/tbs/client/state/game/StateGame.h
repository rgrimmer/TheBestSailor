/* 
 * File:   StateGame.h
 * Author: maxence
 *
 * Created on 16 janvier 2015, 23:28
 */

#ifndef STATEGAME_H
#define	STATEGAME_H

#include <bitset>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Audio/Music.hpp>

#include "client/state/State.h"
#include "client/ClientWorld.h"

#include "client/DetailsView.h"
#include "client/GlobalView.h"

class ClientState;
class ClientNetwork;
class ClientPlayer;

class StateGame : public State {
public:
    StateGame(ClientState& manager, ClientNetwork& network, ClientPlayer& player);
    virtual ~StateGame();


    virtual void initialize();
    virtual void release();

    virtual void activate();
    virtual void deactivate();

    virtual void update(float dt);
    virtual void render(sf::RenderWindow& window) const;

    virtual bool read(MsgData& msg);
    virtual bool read(sf::Event& msg);

    bool readInitGame(MsgData& msg);
    bool readGameInfo(MsgData& msg);
    bool readDisconnect(MsgData& msg);
    bool readCheckpoint(MsgData& msg);
    bool readMsgEnd(MsgData& msg);

private:
    ClientState& m_manager;
    ClientNetwork& m_network;
    ClientPlayer& m_player;
    ClientWorld m_world;

    bool m_hasInfoToSend;
    bool m_isEnded;
    bool m_enableFolowCamera;

    int m_countFrames;
    int m_lastCoutFrames;

    int m_state;

    std::bitset<4> m_keys;

    sf::Drawable* m_mainGraphic;
    DetailsView* m_detailsView;
    GlobalView* m_globalView;
    sf::View m_currentView;

    sf::Music m_music;
    sf::Time m_lastGameInfo;
};

#endif	/* STATEGAME_H */

