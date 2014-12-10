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

#include "client/network/ClientTCPManager.h"
#include "client/network/ClientUDPManager.h"
#include "client/ClientPlayer.h"
#include "shared/SynchronizedQueue.h"
#include "GlobalView.h"

class Client {
public:
    Client();
    virtual ~Client();

    void start(const std::string & name);
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
    
    ClientPlayer m_player;
    
    ClientTCPManager m_tcpManager;
    ClientUDPManager m_udpManager;
    
    std::vector<ClientPlayer> m_otherPlayers;
    SynchronizedQueue<sf::Packet> m_inQueue;
    
    // Graphic
    sf::Drawable* m_mainGraphic;
    DetailsView* m_detailsView;
    GlobalView* m_globalView;
//    HeigthMapView* m_mapView;
//    WindMapView* m_windView;
//    ShipView* m_shipView;

};

#endif	/* CLIENT_H */

