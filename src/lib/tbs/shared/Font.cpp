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
//        if (!g_font->loadFromFile("/usr/share/fonts/truetype/ubuntu-font-family/UbuntuMono-R.ttf"))
        if (!g_font->loadFromFile(getFontString(1)))
            exit(-1);
    }
    return *g_font;
}

std::string Font::getFontString(int index) {
    switch(index) {
        case 1:
            return "./share/tbs/fonts/runescape_uf.ttf";
        case 2:
            return "./share/tbs/fonts/AngillaTattoo_PERSONAL_USE_ONLY.ttf";
        case 3:
            return "./share/tbs/fonts/Kleymissky_0283.otf";
        case 4:
            return "./share/tbs/fonts/Promocyja096.ttf";
        case 5:
            return "./share/tbs/fonts/Zorus_Serif.otf";
        default :
            return "/usr/share/fonts/truetype/ubuntu-font-family/UbuntuMono-R.ttf";
    }
}
