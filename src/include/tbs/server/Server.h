/* 
 * File:   Server.h
 * Author: maxence
 *
 * Created on 9 octobre 2014, 18:30
 */

#ifndef SERVER_H
#define	SERVER_H

#include <list>
#include <vector>

#include "shared/map/Map.h"
#include "server/game/Game.h"
#include "server/game/GameSpeedestWin.h"

#include "server/network/ServerNetwork.h"
//#include "server/serverCheckpoint/ServerCheckpointManager.h"

class ServerNetwork;

class Server {
    friend class ServerNetwork;
public:
    Server();
    virtual ~Server();

    void start(void);
    //    void waitConnections(sf::Packet packet, std::vector<ServerPlayer*>& players);

private:
    void startChronoAndWait();
    void createGame();
    void sendGame();
    void startGame();
    void initializeNetwork();
    Game* m_game;
    std::vector<ServerPlayer*> m_waitingPlayers;

    ServerNetwork* m_serverNetwork;

    //    HeigthMap *m_map;
    //    ServerCheckpointManager m_checkpointManager;


};

#endif	/* SERVER_H */

