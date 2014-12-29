/* 
 * File:   Server.h
 * Author: maxence
 *
 * Created on 9 octobre 2014, 18:30
 */

#ifndef SERVER_H
#define	SERVER_H

#include "shared/network/Semaphore.h"

#include "server/ServerPlayers.h"
#include "server/network/ServerNetwork.h"

class MessageData;
class ServerPlayer;
class ServerGame;

class Server {
public:
    Server();
    virtual ~Server();

    void start(void);

    void pollMessages();
    bool readMessagesWait(sf::Time timeout = sf::Time::Zero);
    bool read(MessageData& message, ServerPlayer& player);

    ServerNetwork* getNetwork();

private:
    void initializeNetwork();
    void startChronoAndWait();
    void createGame();
    void sendGame();
    void startGame();

    void waitAcknowledgment(int permits);

    bool readDisconnect(MessageData& msg, ServerPlayer& player);


private:
    ServerGame* m_game;
    ServerPlayers m_players;

    Semaphore m_acknowledgment;
    ServerNetwork m_network;
};

#endif	/* SERVER_H */

