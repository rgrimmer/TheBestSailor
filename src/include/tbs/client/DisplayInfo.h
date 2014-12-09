/* 
 * File:   DisplayInfo.h
 * Author: maxence
 *
 * Created on 1 novembre 2014, 11:37
 */

#ifndef DISPLAYINFO_H
#define	DISPLAYINFO_H

#include <SFML/Graphics/RenderWindow.hpp>
#include "shared/Font.h"

class DisplayInfo {
public:
    static void setWindow(sf::RenderWindow *window);
    
    static void setTopLeftPosition(const sf::Vector2f &position);
    static void draw(const std::string &text);
    static void setZoom(float zoom);

private:
    
    static sf::RenderWindow *m_window;
    static sf::RenderStates m_states;
    static float m_zoom;

};

#endif	/* DISPLAYINFO_H */

