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

struct node{
    float g_cost, h_cost, f_cost;
    std::pair<int,int> parent;    // 'adresse' du parent (qui sera toujours dans la map fermée
};

typedef std::map<std::pair<int, int>, node> l_node;

class PathFinding {
    
public:
    
    enum area {
        area_center,
        area_south_west,
        area_south_east,
        area_north_east,
        area_north_west 
    };
    
    static int find(sf::Vector2i s, sf::Vector2i e, std::list<sf::Vector2i> &ch);
    static void initialize(float (*level)[NB_TILES_WIDTH][NB_TILES_HEIGHT]);
    static sf::Vector2i choosePoint(area a);
    
private:
    
    static bool isWatterAround(int x, int y, int radius);
    static float distance(int x1, int y1, int x2, int y2);
    static void  add_neightbours(std::pair <int,int>& n);
    static bool isAlreadyIn(std::pair<int,int> n, l_node& l);
    static std::pair<int,int> best_node(l_node& l);
    static void addToClosedList(std::pair<int,int>& p);
    static void retrieve_path();
    
private:
    static float (*m_level)[NB_TILES_WIDTH][NB_TILES_HEIGHT];
};