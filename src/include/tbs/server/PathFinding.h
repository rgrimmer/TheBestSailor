/* 
 * File:   PathFinding.h
 * Author: remy
 *
 * Created on 18 octobre 2014, 16:35
 */

#pragma once

#include <cmath>
#include <map>
#include <list>
#include <iostream>
#include <utility>

#include <SFML/System/Vector2.hpp>

#include "shared/map/Map.h"

struct node {
    float g_cost, h_cost, f_cost;
    std::pair<int, int> parent; // 'adresse' du parent (qui sera toujours dans la map fermée
};

typedef std::map<std::pair<int, int>, node> l_node;

class PathFinding {
public:

    enum area {
        area_center = 0,
        area_north_east = 1,
        area_north_west = 2,
        area_south_west = 3,
        area_south_east = 4
    };

    bool find(sf::Vector2i s, sf::Vector2i e);
    void initialize(const Map* map);
    sf::Vector2i choosePoint(area a);

private:

    bool isWatterAround(int x, int y, int radius);
    float distance(int x1, int y1, int x2, int y2);
    void add_neightbours(std::pair <int, int>& n);
    bool isAlreadyIn(std::pair<int, int> n, l_node& l);
    std::pair<int, int> best_node(l_node& l);
    void addToClosedList(std::pair<int, int>& p);

private:

    const Map* m_map;
    l_node openList;
    l_node closedList;
    std::list<sf::Vector2i> path;
    node start;
    sf::Vector2i end;
};