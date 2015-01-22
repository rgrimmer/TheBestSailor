/* 
 * File:   StateGameStarted.h
 * Author: maxence
 *
 * Created on 18 janvier 2015, 15:54
 */

#ifndef CLIENTSTATEGAMESTARTED_H
#define	CLIENTSTATEGAMESTARTED_H

#include <bitset>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Audio/Music.hpp>

#include "client/state/State.h"
#include "client/network/InputPredictions.h"

class ClientNetwork;
class ClientPlayer;
class ClientWorld;
class DetailsView;
class GlobalView;


class ClientStateGameStarted : public State {
public:
    ClientStateGameStarted(ClientStateGame& manager, ClientNetwork& network, ClientPlayer& player, ClientWorld& world);
    virtual ~ClientStateGameStarted();

    virtual void initialize(void);
    virtual void release(void);
    virtual void activate(void);
    virtual void deactivate(void);
    virtual void update(float dt);
    virtual void render(sf::RenderWindow& window) const;
    virtual bool read(sf::Event& event);
    virtual bool read(MsgData& msg);

private:
    bool readGameInfo(MsgData& msg);
    bool readDisconnect(MsgData& msg);
    bool readCheckpoint(MsgData& msg);
    bool readMsgEnd(MsgData& msg);
    
    bool switchFollowingCamera();
    void sendInfo(const Input &input, sf::Uint32 idReq);
    void updatePrediction(sf::Uint32 idReq);

private:
    ClientStateGame& m_manager;
    ClientNetwork& m_network;
    ClientPlayer& m_player;
    ClientWorld& m_world;
    
    sf::Clock m_clock;
    
    std::bitset<4> m_keys;
    InputPredictions m_predictions;
    bool m_followingCamera;
    float m_zoomValue;
    
    // Graphic
    sf::Drawable* m_mainGraphic;
    DetailsView* m_detailsView;
    GlobalView* m_globalView;
    
    // Sound
    sf::Music m_music;
};

#endif	/* STATEGAMESTARTED_H */

