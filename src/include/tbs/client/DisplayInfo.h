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
    DisplayInfo(sf::RenderWindow *window);
    virtual ~DisplayInfo();
    
    void setTopLeftPosition(const sf::Vector2f &position);
    void draw(const std::string &text);
    void zoom(float zoom);

private:
    
    sf::RenderWindow *m_window;
    sf::RenderStates m_states;
    float m_zoom;

};

#endif	/* DISPLAYINFO_H */

