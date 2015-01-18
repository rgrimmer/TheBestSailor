/* 
 * File:   Client.h
 * Author: maxence
 *
 * Created on 9 octobre 2014, 18:23
 */

#ifndef CLIENT_H
#define	CLIENT_H

#include <thread>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Thread.hpp>

#include "client/ClientPlayer.h"
#include "client/network/ClientNetwork.h"
#include "client/state/ClientState.h"

class Client {
public:
    Client();
    virtual ~Client();

    void start(const std::string & name);
    
    void pollMessages();
    bool pollMessagesWait(sf::Time timeout = sf::Time::Zero);

private:
    sf::RenderWindow m_window;
    ClientNetwork m_network;
    ClientPlayer m_player;
    ClientState m_state;

    sf::Clock m_clock;
};

#endif	/* CLIENT_H */

