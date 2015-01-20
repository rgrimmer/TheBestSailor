/* 
 * File:   ClientStateMenu.h
 * Author: maxence
 *
 * Created on 18 janvier 2015, 10:44
 */

#ifndef MAINMENUSTATEMANAGER_H
#define	MAINMENUSTATEMANAGER_H

#include <string>

#include "client/state/StateManager.h"

enum EMainMenuState {
    ChoiceIp,
    WaitInfo,
    SendInfo
};

class ClientState;
class ClientNetwork;
class ClientPlayer;

class ClientStateMenu : public StateManager<EMainMenuState> {
public:
    ClientStateMenu(ClientState& manager, ClientNetwork& network, ClientPlayer& player);
    virtual ~ClientStateMenu();

    virtual void initialize();
    ClientState& getManager();

private:
    ClientState& m_manager;
    ClientNetwork& m_network;
    ClientPlayer& m_player;

    std::string m_address;


};

#endif	/* MAINMENUSTATEMANAGER_H */

