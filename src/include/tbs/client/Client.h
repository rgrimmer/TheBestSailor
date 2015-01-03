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

class MsgGame;
class ClientGame;
class MsgData;
class MsgServerPlayerInfo;

class Client {
public:
    Client();
    virtual ~Client();

    ClientNetwork& getNetwork();
    const ClientNetwork& getNetwork() const;

    void start(const std::string & name);

    void pollMessages();

private:
    void initConnectionWithServer();
    void initGame();
    void startGame();

    void sendLocalPlayerInfo();
    void waitServerPlayerInfo();

    bool pollMessagesWait(sf::Time timeout = sf::Time::Zero);

    bool read(MsgData& message);
    bool readMsgServerPlayerInfo(MsgData &message);
    bool readMsgGame(MsgData& message);

    void doDisconnection();

private:
    sf::RenderWindow m_window;

    ClientPlayer m_player;
    ClientGame* m_game;

    //    std::vector<ClientPlayer> m_otherPlayers;

    ClientNetwork m_network;
};

#endif	/* CLIENT_H */

