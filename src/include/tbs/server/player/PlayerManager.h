/* 
 * File:   PlayerManager.h
 * Author: maxence
 *
 * Created on 20 octobre 2014, 18:27
 */

#ifndef PLAYERMANAGER_H
#define	PLAYERMANAGER_H

#include <vector>

#include "shared/entity/Player.h"

class PlayerManager {
public:
    PlayerManager();
    PlayerManager(const PlayerManager& orig);
    virtual ~PlayerManager();
    
    void addPlayer(const Player &player);
    void addPlayer(Player* player);

private:
    std::vector<Player*> m_players;

};

#endif	/* PLAYERMANAGER_H */

