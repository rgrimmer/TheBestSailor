/* 
 * File:   Client.h
 * Author: maxence
 *
 * Created on 9 octobre 2014, 18:23
 */

#ifndef CLIENT_H
#define	CLIENT_H

#include <thread>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Thread.hpp>

#include "shared/ship/Ship.h"
#include "shared/SynchronizedQueue.h"

#include "client/DetailsView.h"
#include "client/World.h"
#include "client/network/ClientTCPManager.h"
#include "client/network/ClientUDPManager.h"
#include "client/ClientPlayer.h"
#include "GlobalView.h"

class Client {
public:
    Client();
    virtual ~Client();

    void start(const std::string & name);
private:
    void initConnectionWithServer();
    void initGame();
    bool startGame();

    // @Temporary

    void receive();
    void gameLoop(sf::RenderWindow *window);

private:
    sf::RenderWindow m_window;
    World m_world;
    //HeigthMap* m_map;
    //WindMap* m_wind;
    //Ship m_ship;
    bool m_enableFolowCamera;
    bool m_enablePause;
    float m_timeSpeed;

    ClientPlayer m_player;

    std::thread* m_udpReceiveThread;
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

