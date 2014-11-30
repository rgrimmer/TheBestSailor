/* 
 * File:   ClientPlayer.h
 * Author: remy
 *
 * Created on 30 novembre 2014, 18:42
 */

#ifndef CLIENT_PLAYER_H
#define	CLIENT_PLAYER_H

#include <string>

class ClientPlayer {
    
public:
    ClientPlayer(std::string name);
    ~ClientPlayer();
private:
    std::string m_name;
};

#endif	/* CLIENT_PLAYER_H */

