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

#include "shared/map/MapHeader.h"
#include "shared/map/HeigthMap.h"
#include "shared/map/WindMap.h"
#include "shared/ship/Ship.h"

#include "client/DetailsView.h"
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
    Ship m_ship;
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
    DetailsView* m_detailsView;
//    HeigthMapView* m_mapView;
//    WindMapView* m_windView;
//    ShipView* m_shipView;

};

#endif	/* CLIENT_H */

