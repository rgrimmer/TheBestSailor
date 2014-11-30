/* 
 * File:   Font.cpp
 * Author: maxence
 * 
 * Created on 28 novembre 2014, 11:20
 */

#include "shared/Font.h"

sf::Font *Font::g_font = 0;

Font::Font() {
}

Font::~Font() {
}

sf::Font& Font::getFont() {
    if(g_font == 0) {
        g_font = new sf::Font;
        if (!g_font->loadFromFile("/usr/share/fonts/truetype/ubuntu-font-family/UbuntuMono-R.ttf"))
            exit(-1);
    }
    return *g_font;
}

