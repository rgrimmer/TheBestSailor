/* 
 * File:   TextView.h
 * Author: maxence
 *
 * Created on 1 novembre 2014, 11:37
 */

#ifndef TEXTVIEW_H
#define	TEXTVIEW_H

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Text.hpp>
#include "shared/Font.h"

#include <string>

enum TypeAlign {
    Regular,
    Center,
};

class TextView : public sf::Drawable {
public:
    TextView(const std::string& text, int size = 30, TypeAlign type = Regular, sf::Uint32 = sf::Text::Style::Regular);
    virtual ~TextView();
    
    static void update();
    static void setAbs(bool drawAbs);
    
private:
    static sf::IntRect g_prevViewport;
    static bool g_absView;
    static sf::RenderStates g_states;
    
private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void drawText(sf::RenderTarget& target) const;
    
private:
    std::string m_text;
    int m_size;
    TypeAlign m_type;
    sf::Uint32 m_style;
    

};

#endif	/* TEXTVIEW_H */

