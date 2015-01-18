/* 
 * File:   StateMainMenuChoiceIp.h
 * Author: maxence
 *
 * Created on 18 janvier 2015, 11:06
 */

#ifndef STATEMAINMENUCHOICEIP_H
#define	STATEMAINMENUCHOICEIP_H

#include "client/ChoiceIpView.h"
#include "client/state/State.h"
#include "client/state/mainMenu/MainMenuStateManager.h"

class StateMainMenuChoiceIp : public State {
public:
    StateMainMenuChoiceIp(MainMenuStateManager& manager, std::string& address);
    virtual ~StateMainMenuChoiceIp();

public:
    virtual void initialize();
    virtual void release();
    virtual void activate();
    virtual void deactivate();
    virtual void update(float dt);
    virtual void render(sf::RenderWindow& window) const;
    virtual bool read(sf::Event& event);
    virtual bool read(MsgData& msg);

private:
    MainMenuStateManager& m_manager;
    std::string& m_address;
    
    ChoiceIpView m_choiceIpView;
};

#endif	/* STATEMAINMENUCHOICEIP_H */

