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
    Map(const Map& orig);
    virtual ~Map();
    
    void generate(int width, int height);
    inline int size() const { return m_width * m_height; }
    inline int width() const { return m_width; }
    inline int& rwidth() { return m_width; }
    inline int height() const { return m_height; }    
    inline int& rheight() { return m_height; }    
    
    float& operator[](unsigned indice) {
        return m_container[indice];
    }
    
    // sf::Packet& operator<<(sf::Packet &packet);
    // sf::Packet& operator>>(sf::Packet &packet);
    
private:
    float *m_container;
    int m_width;
    int m_height;

};

#endif	/* MAP_H */

