/* 
 * File:   ClientStateMenuExchangeInfo.h
 * Author: maxence
 *
 * Created on 18 janvier 2015, 13:58
 */

#ifndef ClientStateMenuExchangeInfo_H
#define	ClientStateMenuExchangeInfo_H

#include <SFML/Network/IpAddress.hpp>

#include "client/state/State.h"
#include "client/view/ConnectionView.h"

class ClientStateMenu;
class ClientNetwork;
class ClientPlayer;

class ClientStateMenuExchangeInfo : public State {
public:
    ClientStateMenuExchangeInfo(ClientStateMenu& manager, ClientNetwork& network, ClientPlayer& player, std::string& address);
    virtual ~ClientStateMenuExchangeInfo();

    virtual void release(void);
    virtual void activate(void);
    virtual void deactivate(void);
    virtual void update(float dt);
    virtual void render(sf::RenderWindow& window) const;
    virtual bool read(sf::Event& event);
    virtual bool read(MsgData& msg);

private:
    void initConnectionWithServer(void);
    void sendLocalPlayerInfo(void);

    bool readMsgServerPlayerInfo(MsgData& msg);

private:
    ClientStateMenu& m_manager;
    ClientNetwork& m_network;
    ClientPlayer& m_player;
    std::string& m_stdAddress;
    sf::IpAddress m_address;
    unsigned short m_port;
    
    ConnectionView m_connectionView;
    

};

#endif	/* ClientStateMenuExchangeInfo_H */

