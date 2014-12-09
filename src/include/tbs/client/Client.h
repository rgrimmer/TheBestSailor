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

#include "shared/map/MapHeader.h"
#include "shared/map/HeigthMap.h"
#include "shared/map/WindMap.h"
#include "shared/ship/Ship.h"

#include "client/DetailsView.h"

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
    Ship m_ship;
    bool m_enableFolowCamera;
    bool m_enablePause;
    float m_timeSpeed;
    
    // Graphic
    DetailsView* m_detailsView;
//    HeigthMapView* m_mapView;
//    WindMapView* m_windView;
//    ShipView* m_shipView;

};

#endif	/* CLIENT_H */

