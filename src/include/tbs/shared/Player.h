/* 
 * File:   Player.h
 * Author: maxence
 *
 * Created on 20 octobre 2014, 18:28
 */

#ifndef PLAYER_H
#define	PLAYER_H

#include <string>
#include "shared/network/SocketQueuBuffer.h"

class Player {
public:
    Player(const std::string& name = "noName", SocketQueuBuffer *buffer = NULL);
    Player(const Player& orig);
    virtual ~Player();
    
    const std::string& getName() const;
private:
    
    std::string m_name;
    SocketQueuBuffer *m_buffer;
    

};

#endif	/* PLAYER_H */

