/* 
 * File:   World.h
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

class World {
    
public:
    explicit World();
    virtual ~World();
    
    void initialize();
    void release();
    
    void setMap(Map* map);
    void initializeMap(int height, int width, double seed);
    
    void update(float dt);
    
    Ship& getShip();
    WindMap& getWind() const;
    HeigthMap& getMap() const;
    
private:
    Map* m_mapmap;
//    HeigthMap* m_map;
//    WindMap* m_wind;
    Ship m_ship;
};

#endif	/* WORLD_H */

