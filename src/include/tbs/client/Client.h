/* 
 * File:   Client.h
 * Author: maxence
 *
 * Created on 9 octobre 2014, 18:23
 */

#ifndef CLIENT_H
#define	CLIENT_H

#include <SFML/Network.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
//#include <thread>
#include <SFML/System/Thread.hpp>

#include "client/ship/DrawShip.h"
#include "client/map/TileMap.h"


#include "shared/map/WindMap.h"
#include "shared/ship/Ship.h"
#include "shared/map/MapHeader.h"
#include "shared/map/DrawWind.h"
#include "shared/map/HeigthMap.h"
class Client {
public:
    Client();
    virtual ~Client();

    void start(void);
private:
    void gameLoop(sf::RenderWindow *window);
    
private:
    sf::TcpSocket m_socket;

    HeigthMap* m_map;
    WindMap* m_wind;
    TileMap m_mapView;
    Ship m_ship;
    bool m_enableWind;
    bool m_enableFolowCamera;
    bool m_enablePause;
    float m_timeSpeed;
    
    // Graphic
    DrawShip m_shipView;
    DrawWind m_windView;

};

#endif	/* CLIENT_H */

