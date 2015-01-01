/* 
 * File:   ClientGame.h
 * Author: maxence
 *
 * Created on 17 décembre 2014, 16:50
 */

#ifndef CLIENTGAME_H
#define	CLIENTGAME_H

#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class MsgData;
class Client;

class ClientGame {
public:
    ClientGame(sf::RenderWindow& window, Client& client);
    virtual ~ClientGame();

    void start();
    virtual bool read(MsgData& msg) = 0;
    virtual void setUpdateTime(const sf::Time& updateTime);

protected:
    virtual void init() = 0;
    virtual void update(float dt) = 0;
    virtual void draw() = 0;
    virtual bool isEnded() = 0;
    virtual bool read(sf::Event& event) = 0;
    virtual void sendInfo() {}
    
private:
    void displayView();

protected:
    sf::RenderWindow& m_window;
    Client& m_client;
    sf::Time m_updateTime;
    bool m_hasInfoToSend;
    
    sf::Clock m_clockFPS;
    int m_countFrames;
    int m_lastCoutFrames;

};

#endif	/* CLIENTGAME_H */

