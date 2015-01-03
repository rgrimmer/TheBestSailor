/* 
 * File:   ClientWorld.h
 * Author: remy
 *
 * Created on 10 décembre 2014, 16:15
 */

#ifndef WORLD_H
#define	WORLD_H

#include <map>
#include <iostream>

#include "client/checkpoint/ClientCheckPointManager.h"

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

    void addCheckPoint(sf::Vector2i position);
    
    std::map<unsigned int, Ship>& getShips();
    const std::map<unsigned int, Ship>& getShips() const;
    void setClientShip(Ship* ship);
    
    Ship& getClientShip();
    const Ship& getClientShip() const;

    bool windComeFromTribord(const Wind &wind) const;
    bool windComeFromFront(const Wind &wind) const;

 
    ClientCheckPointManager& getCheckPointManager();
    
    Map& getMap();
    const Map& getMap() const;

    HeigthMap& getHeightMap();
    const HeigthMap& getHeightMap() const;

    WindMap& getWindMap();
    const WindMap& getWindMap() const;

private:
    Map m_mapmap;
    ClientCheckPointManager* m_checkPointManager;
    Ship* m_ship;
    std::map<unsigned int, Ship> m_ships;
};

sf::Packet& operator>>(sf::Packet& packet, ClientWorld& world);

#endif	/* WORLD_H */

