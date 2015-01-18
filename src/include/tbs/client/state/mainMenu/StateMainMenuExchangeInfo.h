/* 
 * File:   StateMainMenuExchangeInfo.h
 * Author: maxence
 *
 * Created on 18 janvier 2015, 13:58
 */

#ifndef STATEMAINMENUEXCHANGEINFO_H
#define	STATEMAINMENUEXCHANGEINFO_H

#include <SFML/Network/IpAddress.hpp>

#include "client/state/State.h"
#include "client/ConnectionView.h"

class MainMenuStateManager;
class ClientNetwork;
class ClientPlayer;

class StateMainMenuExchangeInfo : public State {
public:
    StateMainMenuExchangeInfo(MainMenuStateManager& manager, ClientNetwork& network, ClientPlayer& player, std::string& address);
    virtual ~StateMainMenuExchangeInfo();

    virtual void initialize(void);
    virtual void release(void);
    virtual void activate(void);
    virtual void deactivate(void);
    virtual void update(float dt);
    virtual void render(sf::RenderWindow& window) const;
    virtual bool read(sf::Event& event);
    virtual bool read(MsgData& msg);

private:
    void initConnectionWithServer(const sf::IpAddress &address);
    void sendLocalPlayerInfo();

    bool readMsgServerPlayerInfo(MsgData& msg);

private:
    MainMenuStateManager& m_manager;
    ClientNetwork& m_network;
    ClientPlayer& m_player;
    sf::IpAddress m_address;
    
    ConnectionView m_connectionView;
    

};

#endif	/* STATEMAINMENUEXCHANGEINFO_H */

