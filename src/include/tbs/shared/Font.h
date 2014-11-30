/* 
 * File:   Font.h
 * Author: maxence
 *
 * Created on 28 novembre 2014, 11:20
 */

#ifndef FONT_H
#define	FONT_H

#include <SFML/Graphics/Font.hpp>

class Font {
public:
    static sf::Font& getFont();
    
private:
    static sf::Font *g_font;
    
    Font();
    virtual ~Font();

};

#endif	/* FONT_H */

