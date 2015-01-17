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
#include "game/ClientGameConnection.h"
#include "gamestate/GameStateManager.h"
#include "state/ClientState.h"

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

private:
    void initConnectionWithServer(const sf::IpAddress &address);
    void initGame();
    void startGame();

    void sendLocalPlayerInfo();
    void waitServerPlayerInfo();

    void pollMessages();
    bool pollMessagesWait(sf::Time timeout = sf::Time::Zero);

    bool read(MsgData& message);
    bool readMsgServerPlayerInfo(MsgData &message);
    bool readMsgGame(MsgData& message);

    void doDisconnection();

private:
//    GameStateManager m_gamestateManager;
    sf::RenderWindow m_window;

    sf::Clock m_clock;
    
    ClientPlayer m_player;
    ClientGame* m_game;
    ClientGameConnection* m_connection;
    ClientState m_state;

    //    std::vector<ClientPlayer> m_otherPlayers;

    ClientNetwork m_network;
};

#endif	/* CLIENT_H */

