/* 
 * File:   Map.h
 * Author: maxence
 *
 * Created on 10 octobre 2014, 13:39
 */

#ifndef MAP_H
#define	MAP_H

#include <assert.h>
#include <SFML/Network/Packet.hpp>

class Map {
public:
    Map();
    Map(int width, int height, double seed);
    virtual ~Map();

    void allocate(int width, int height);
    
    float& operator()(int i, int j) {
        return m_container[i][j];
    }

    float operator()(int i, int j) const {
        return m_container[i][j];
    }
    
    int getSize() const;
    int getWidth() const;
    int getHeight() const;

private:
    int m_width;
    int m_height;
    float** m_container;
};

#endif	/* MAP_H */

