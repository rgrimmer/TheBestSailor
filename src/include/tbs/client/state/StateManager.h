#pragma once

#include <stack>
#include <unordered_map>

#include "client/state/State.h"

template<typename T> class StateManager;

template<typename T>
class StateManager : public State {
public:

    explicit StateManager(void);
    virtual ~StateManager(void);

    // State interface
    virtual void release(void);
    virtual void activate(void);
    virtual void deactivate(void);
    virtual void update(float dt);
    virtual void render(sf::RenderWindow& window) const;
    virtual bool read(sf::Event& event);
    virtual bool read(MsgData& msg);

    // Manager access
    void add(T eState, State* state);
    void push(T eState);
    void pop(void);
    void change(T eState);
    void reset(void);
    virtual void create(T eState) = 0;
    virtual T firstState() const = 0;

protected:
    State* getCurrentState(void) const;

protected:
    std::unordered_map<unsigned int, State*> m_apState;
    std::stack<State*> m_sState;
};

template<typename T>
StateManager<T>::StateManager(void)
: m_apState()
, m_sState() {

}

template<typename T>
StateManager<T>::~StateManager(void) {

}

template<typename T>
void StateManager<T>::release(void) {
    while (!m_sState.empty()) {
        m_sState.top()->release();
        m_sState.pop();
    }
}

template<typename T>
void StateManager<T>::reset(void) {
    if(m_sState.size() == 0) {
        push(firstState());
        return;
    }
    while (m_sState.size() > 1) {
        m_sState.pop();
    }
    m_sState.top()->activate();
}

template<typename T>
void StateManager<T>::activate(void) {
    reset();
}

template<typename T>
void StateManager<T>::deactivate(void) {
    m_sState.top()->deactivate();
}

template<typename T>
void StateManager<T>::update(float dt) {
    m_sState.top()->update(dt);
}

template<typename T>
void StateManager<T>::render(sf::RenderWindow& window) const {
    m_sState.top()->render(window);
}

template<typename T>
bool StateManager<T>::read(sf::Event& event) {
    return m_sState.top()->read(event);
}

template<typename T>
bool StateManager<T>::read(MsgData& msg) {
    return m_sState.top()->read(msg);
}

template<typename T>
void StateManager<T>::add(T eState, State* state) {
    m_apState[eState] = state;
}

template<typename T>
void StateManager<T>::push(T eState) {
    State* pCurrentState = getCurrentState();

    if (nullptr != pCurrentState) {
        pCurrentState->deactivate();
    }

    if (m_apState.find(eState) == m_apState.end())
        create(eState);

    m_sState.push(m_apState[eState]);
    m_apState[eState]->activate();
}

template<typename T>
void StateManager<T>::pop(void) {
    State* pCurrentState = getCurrentState();

    if (nullptr != pCurrentState) {
        pCurrentState->deactivate();
        m_sState.pop();
    }

    getCurrentState()->activate();
}

template<typename T>
void StateManager<T>::change(T eState) {
    //pop
    State* pCurrentState = getCurrentState();

    if (nullptr != pCurrentState) {
        pCurrentState->deactivate();
    }

    m_sState.pop();

    //push
    if (m_apState.find(eState) == m_apState.end())
        create(eState);

    m_sState.push(m_apState[eState]);

    m_apState[eState]->activate();

}

template<typename T>
State * StateManager<T>::getCurrentState(void) const {
    if (m_sState.empty())
        return nullptr;

    return m_sState.top();
}
