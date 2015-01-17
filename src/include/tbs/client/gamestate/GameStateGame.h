/* 
 * File:   GameStateWaitGame.h
 * Author: maxence
 *
 * Created on 16 janvier 2015, 23:28
 */

#ifndef GAMESTATEGAME_H
#define	GAMESTATEGAME_H

#include <bitset>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Audio/Music.hpp>

#include "client/gamestate/GameState.h"
#include "client/ClientWorld.h"

#include "client/DetailsView.h"
#include "client/GlobalView.h"

class GameStateGame : public GameState {
public:
    GameStateGame(sf::RenderWindow& window, ClientNetwork& network, ClientPlayer& player);
    virtual ~GameStateGame();


    virtual void Initialize();
    virtual void Release();

    virtual void Activate();
    virtual void DeActivate();

    virtual void Update(float dt);
    virtual void Render(sf::RenderWindow& window);

    virtual bool read(MsgData& msg);
    virtual bool read(sf::Event& msg);
    
    bool readInitGame(MsgData& msg);
    bool readGameInfo(MsgData& msg);
    bool readDisconnect(MsgData& msg);
    bool readCheckpoint(MsgData& msg);
    bool readMsgEnd(MsgData& msg);

private:
    ClientWorld m_world;
    
    bool m_hasInfoToSend;
    bool m_isEnded;
    bool m_enableFolowCamera;
    
    int m_countFrames;
    int m_lastCoutFrames;
    
    std::bitset<4> m_keys;

    sf::Drawable* m_mainGraphic;
    DetailsView* m_detailsView;
    GlobalView* m_globalView;
    sf::View m_currentView;
    
    sf::Music m_music;
    sf::Time m_lastGameInfo;
};

#endif	/* GAMESTATEGAME_H */

