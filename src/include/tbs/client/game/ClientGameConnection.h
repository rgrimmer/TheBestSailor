/* 
 * File:   ClientGameConnection.h
 * Author: maxence
 *
 * Created on 31 décembre 2014, 17:43
 */

#ifndef CLIENTGAMECONNECTION_H
#define	CLIENTGAMECONNECTION_H

#include <string>

#include <SFML/Network/IpAddress.hpp>

#include "client/game/ClientGame.h"
#include "client/ConnectionView.h"

class ClientGameConnection : public ClientGame {
public:
    ClientGameConnection(sf::RenderWindow& window, Client& client);
    virtual ~ClientGameConnection();

    unsigned short getPort() const;
    sf::IpAddress getIpAddress() const;

    virtual bool read(MsgData& msg);

protected:
    virtual void init();
    virtual void update(float dt);
    virtual void draw();
    virtual bool isEnded();

    virtual bool read(sf::Event& event);

private:
    bool m_validate;
    unsigned short m_port;
    sf::IpAddress m_address;
    
    std::string m_ipAddressInput;
    ConnectionView m_view;

};

#endif	/* CLIENTGAMECONNECTION_H */

