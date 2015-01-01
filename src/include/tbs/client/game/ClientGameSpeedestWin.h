/* 
 * File:   ClientGameSpeedestWin.h
 * Author: maxence
 *
 * Created on 14 décembre 2014, 19:15
 */

#ifndef CLIENTGAMESPEEDESTWIN_H
#define	CLIENTGAMESPEEDESTWIN_H

#include <bitset>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderWindow.hpp>


#include "client/ClientWorld.h"
#include "client/game/ClientGame.h"

class DetailsView;
class GlobalView;
class Client;

class ClientGameSpeedestWin : public ClientGame {
public:
    ClientGameSpeedestWin(sf::RenderWindow& window, Client &client, ClientPlayer& player);
    virtual ~ClientGameSpeedestWin();

    virtual bool read(MsgData& msg);
    virtual bool read(sf::Event& event);

    void setClientWorld(const ClientWorld &world);
    const ClientWorld& getClientWorld() const;

protected:
    virtual void init();
    virtual void update(float dt);
    virtual void draw();
    virtual bool isEnded();
    virtual void sendInfo();

private:
    void release();
    bool readInitGame(MsgData& msg);
    bool readGameInfo(MsgData& msg);
    bool readDisconnect(MsgData& msg);

private:
    // Model
    ClientWorld m_world;

    // Network
    ClientPlayer& m_player;
    sf::Clock m_clockGame;
    sf::Time m_lastGameInfo;

    bool m_enableFolowCamera;
    bool m_enablePause;
    float m_timeSpeed;
    sf::Vector2f m_posView;
    float m_zoomValue;
    
    std::bitset<4> m_keys;

    sf::Drawable* m_mainGraphic;
    DetailsView* m_detailsView;
    GlobalView* m_globalView;
    sf::View m_currentView;
};

#endif	/* CLIENTGAMESPEEDESTWIN_H */

