/* 
 * File:   ConnectionView.h
 * Author: maxence
 *
 * Created on 31 décembre 2014, 11:24
 */

#ifndef CONNECTIONVIEW_H
#define	CONNECTIONVIEW_H

#include <string>

#include <SFML/Graphics/View.hpp>

#include "client/view/TextView.h"
#include "client/view/menu/MenuView.h"

class ConnectionView : public MenuView {
public:
    ConnectionView();
    virtual ~ConnectionView();

    void setAdressText(const std::string& ipAddress);

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    sf::View m_ipAddressSfView;
    TextView m_fixedTextView;
    std::string m_ipAddressText;
};

#endif	/* CONNECTIONVIEW_H */

