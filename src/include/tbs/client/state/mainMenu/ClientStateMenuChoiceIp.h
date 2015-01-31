/* 
 * File:   ClientStateMenuChoiceIp.h
 * Author: maxence
 *
 * Created on 18 janvier 2015, 11:06
 */

#ifndef ClientStateMenuChoiceIp_H
#define	ClientStateMenuChoiceIp_H

#include "client/view/ChoiceIpView.h"
#include "client/state/State.h"
#include "client/state/mainMenu/ClientStateMenu.h"

class ClientStateMenuChoiceIp : public State {
public:
    ClientStateMenuChoiceIp(ClientStateMenu& manager, std::string& address);
    virtual ~ClientStateMenuChoiceIp();

public:
    virtual void release();
    virtual void activate();
    virtual void deactivate();
    virtual void update(float dt);
    virtual void render(sf::RenderWindow& window) const;
    virtual bool read(sf::Event& event);
    virtual bool read(MsgData& msg);

private:
    ClientStateMenu& m_manager;
    std::string& m_address;
    
    ChoiceIpView m_choiceIpView;
};

#endif	/* ClientStateMenuChoiceIp_H */

