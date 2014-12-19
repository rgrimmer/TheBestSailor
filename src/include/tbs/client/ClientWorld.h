/* 
 * File:   ClientWorld.h
 * Author: remy
 *
 * Created on 10 décembre 2014, 16:15
 */

#ifndef WORLD_H
#define	WORLD_H

#include <iostream>

#include "shared/map/MapHeader.h"
#include "shared/map/HeigthMap.h"
#include "shared/map/WindMap.h"
#include "shared/map/Map.h"
#include <shared/ship/Ship.h>

class ClientWorld {
public:
    explicit ClientWorld();
    virtual ~ClientWorld();

    void initialize();

    void setMap(const Map& map);
    void initializeMap(int width, int height, int heightMapSeed, int windMapSeed);

    void update(float dt);

    Ship& getShip();
    const Ship& getShip() const;
    
    Map& getMap();
    const Map& getMap() const;
    
    HeigthMap& getHeightMap();
    const HeigthMap& getHeightMap() const;
    
    WindMap& getWindMap();
    const WindMap& getWindMap() const;

private:
    Map m_mapmap;
    Ship m_ship;
};

sf::Packet& operator>>(sf::Packet& packet, ClientWorld& world);

#endif	/* WORLD_H */

