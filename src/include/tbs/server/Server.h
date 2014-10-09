/* 
 * File:   Server.h
 * Author: maxence
 *
 * Created on 9 octobre 2014, 18:30
 */

#ifndef SERVER_H
#define	SERVER_H

#include <SFML/Network.hpp>

#include "../shared/TileMap.h"

class Server {
public:
    Server();
    Server(const Server& orig);
    virtual ~Server();
    
    void start(void);
    void generateMap(TileMap& map, int width, int heigth);

private:
    TileMap *map;

};

#endif	/* SERVER_H */

