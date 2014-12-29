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
class MessageData;
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
    bool startGame();

    void sendLocalPlayerInfo();
    void waitServerPlayerInfo();

    bool pollMessagesWait(sf::Time timeout = sf::Time::Zero);

    bool read(MessageData& message);
    bool readMsgServerPlayerInfo(MessageData &message);
    bool readMsgGame(MessageData& message);

    //    bool read(MsgGame& message);
    //    bool read(MsgServerPlayerInfo& message);

private:
    sf::RenderWindow m_window;

    ClientPlayer m_player;
    ClientGame* m_game;

    //    std::vector<ClientPlayer> m_otherPlayers;

    ClientNetwork m_network;
};

#endif	/* CLIENT_H */

