/* 
 * File:   ClientGameSpeedestWin.h
 * Author: maxence
 *
 * Created on 14 décembre 2014, 19:15
 */

#ifndef CLIENTGAMESPEEDESTWIN_H
#define	CLIENTGAMESPEEDESTWIN_H

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderWindow.hpp>


#include "client/ClientWorld.h"
#include "client/game/ClientGame.h"

class DetailsView;
class GlobalView;
class Client;

class ClientGameSpeedestWin : public ClientGame {
public:
    ClientGameSpeedestWin(Client &client, ClientPlayer& player, sf::RenderWindow& m_window);
    virtual ~ClientGameSpeedestWin();

    virtual bool read(MsgData& msg);
    virtual bool readInitGame(MsgData& msg);

    void setClientWorld(const ClientWorld &world);
    const ClientWorld& getClientWorld() const;

private:
    void initGame();
    bool startGameLoop();
    void release();

private:
    bool readGameInfo(MsgData& msg);
    bool readDisconnect(MsgData& msg);
    
private:
    // Model
    ClientWorld m_world;

    // Network
    Client& m_client;
    ClientPlayer& m_player;
    sf::Clock m_clockGame;
    sf::Time m_lastGameInfo;

    // Graphic
    sf::RenderWindow& m_window;

    bool m_enableFolowCamera;
    bool m_enablePause;
    float m_timeSpeed;
    sf::Vector2f m_posView;
    float m_zoomValue;

    sf::Drawable* m_mainGraphic;
    DetailsView* m_detailsView;
    GlobalView* m_globalView;
};

MsgGame& operator>>(MsgGame &msg, ClientGameSpeedestWin& game);

#endif	/* CLIENTGAMESPEEDESTWIN_H */

