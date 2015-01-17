#pragma once

#include <stack>
#include <unordered_map>

#include "client/state/State.h"

template<typename T> class StateManager;

template<typename T>
class StateManager : State {
public:

    explicit StateManager(void);
    virtual ~StateManager(void);

    // State interface
    virtual void initialize(void) =0;
    virtual void release(void);
    virtual void activate(void);
    virtual void deActivate(void);
    virtual void update(float dt);
    virtual void render(sf::RenderWindow& window) const;
    virtual bool read(sf::Event& event);
    virtual bool read(MsgData& msg);

    // Manager access
    void add(T eState, State* state);
    void push(T eState);
    void pop(void);
    void change(T eState);

protected:
    State* getCurrentState(void) const;

    std::unordered_map<unsigned int, State*> m_apState;
    T m_eCurrentState;
    std::stack<State*> m_sState;
};

template<typename T>
StateManager<T>::StateManager(void)
: m_apState()
, m_eCurrentState()
, m_sState() {

}

template<typename T>
StateManager<T>::~StateManager(void) {

}

template <typename T>   
void StateManager<T>::initialize(void) {
    
//    m_apState[EClientState::e_game_state_main_menu] = new StateMainMenu(window, network, player);
//    m_apState[EClientState::e_game_state_wait_game] = new StateWaitGame(window, network, player);
//
//    m_apState[EClientState::e_game_state_main_menu]->Initialize();
//
//    m_eCurrentState = EClientState::e_game_state_main_menu;
//    Push(m_eCurrentState);
}

template<typename T>
void StateManager<T>::release(void) {
    while (!m_sState.empty()) {
        m_sState.top()->release();
        m_sState.pop();
    }
}


/*
void StateManager::UpdateAndRender(sf::RenderWindow& window, float dt) {
    State* pCurrentState = GetCurrentState();

    if (nullptr != pCurrentState) {

        sf::Event event;
        while (window.pollEvent(event)) {

            if (!pCurrentState->read(event)) {
                window.close();
            }
        }
        
        pCurrentState->pollMessages();

        pCurrentState->Update(dt);
        window.clear(sf::Color(5, 52, 79, 255));
        pCurrentState->Render(window);

        TextView::setAbs(true);
        TextView::update();

        window.display();
    }
}*/

template<typename T>
void StateManager<T>::activate(void) {
    getCurrentState()->activate();
}

template<typename T>
void StateManager<T>::deActivate(void) {
    getCurrentState()->deActivate();
}

template<typename T>
void StateManager<T>::update(float dt) {
    getCurrentState()->update(dt);
}

template<typename T>
void StateManager<T>::render(sf::RenderWindow& window) const {
    getCurrentState()->render(window);
}

template<typename T>
bool StateManager<T>::read(sf::Event& event) {
    return getCurrentState()->read(event);
}

template<typename T>
bool StateManager<T>::read(MsgData& msg) {
    return getCurrentState()->read(msg);
}

template<typename T>
void StateManager<T>::add(T eState, State* state) {
    m_apState[eState] = state;
}

template<typename T>
void StateManager<T>::push(T eState) {
    State* pCurrentState = getCurrentState();

    if (nullptr != pCurrentState) {
        pCurrentState->deActivate();
    }

    m_apState[eState]->activate();
    m_eCurrentState = eState;

    m_sState.push(m_apState[eState]);
}

template<typename T>
void StateManager<T>::pop(void) {
    State* pCurrentState = getCurrentState();

    if (nullptr != pCurrentState) {
        m_sState.pop();
    }

    getCurrentState()->activate();
}

template<typename T>
void StateManager<T>::change(T eState) {
    //pop
    State* pCurrentState = getCurrentState();

    if (nullptr != pCurrentState) {
        pCurrentState->deActivate();
    }

    m_sState.pop();

    //push
    m_apState[eState]->activate();
    m_eCurrentState = eState;

    m_sState.push(m_apState[eState]);
}

template<typename T>
State * StateManager<T>::getCurrentState(void) const {
    if (m_sState.empty())
        return nullptr;

    return m_sState.top();
}