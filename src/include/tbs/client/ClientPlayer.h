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
    ClientPlayer(const unsigned int id, const std::string & name);
    ~ClientPlayer();

    void setName(const std::string & name);
    void setId(const unsigned int id);
    const std::string& getName() const;
    unsigned int getId() const;

private:
    std::string m_name;
    unsigned int m_id;

};

#endif	/* CLIENT_PLAYER_H */

