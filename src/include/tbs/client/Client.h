/* 
 * File:   Client.h
 * Author: maxence
 *
 * Created on 9 octobre 2014, 18:23
 */

#ifndef CLIENT_H
#define	CLIENT_H

#include <SFML/Graphics/RenderWindow.hpp>
//#include <thread>
#include <SFML/System/Thread.hpp>

#include "client/ship/DrawShip.h"
#include "client/map/TileMap.h"
#include "client/ClientPlayer.h"
#include "client/network/ClientTCPManager.h"
#include "client/network/ClientUDPManager.h"

#include "shared/map/WindMap.h"
#include "shared/ship/Ship.h"
#include "shared/map/MapHeader.h"
#include "shared/map/DrawWind.h"
#include "shared/map/HeigthMap.h"
#include "shared/SynchronizedQueue.h"

class Client {
public:
    Client();
    virtual ~Client();

    void start(void);
private:
    static void receive(ClientUDPManager& udpManager, SynchronizedQueue<sf::Packet>& inQueue);
    void gameLoop(sf::RenderWindow *window);
    
private:
    HeigthMap* m_map;
    WindMap* m_wind;
    TileMap m_mapView;
    Ship m_ship;
    bool m_enableWind;
    bool m_enableFolowCamera;
    bool m_enablePause;
    float m_timeSpeed;
    
    ClientTCPManager m_tcpManager;
    ClientUDPManager m_udpManager;
    
    // Graphic
    DrawShip m_shipView;
    DrawWind m_windView;
    
    std::vector<ClientPlayer> m_otherPlayers;
    std::string m_name;
    
    SynchronizedQueue<sf::Packet> m_inQueue;

};

#endif	/* CLIENT_H */

