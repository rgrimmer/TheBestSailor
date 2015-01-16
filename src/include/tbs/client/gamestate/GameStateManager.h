#pragma once

#include <stack>

#include "GameState.h"

class GameStateManager {
public:


    explicit GameStateManager(void);
    virtual ~GameStateManager(void);

    void Initialize(sf::RenderWindow& window, ClientNetwork& network, ClientPlayer& player);
    void Release(void);

    void UpdateAndRender(sf::RenderWindow & window, float dt);
    
    // GameState access
    void Push(GameState::EGameState eGameState);
    void Pop(void);
    void Change(GameState::EGameState eGameState);

    GameState* GetCurrentGameState(void) const;

private:
    GameState* m_apGameState[GameState::EGameState::e_game_state_max];
    GameState::EGameState m_eCurrentGameState;
    std::stack<GameState*> m_sGameState;
};

extern GameStateManager g_gameStateManager;