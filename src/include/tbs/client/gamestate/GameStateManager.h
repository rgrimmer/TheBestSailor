#pragma once

#include <stack>

#include "GameState.h"

class GameStateManager {
public:

    enum EGameState {
        e_game_state_main_menu,
        e_game_state_max
    };

    explicit GameStateManager(void);
    virtual ~GameStateManager(void);

    void Initialize(void);
    void Release(void);

    void UpdateAndRender(float dt);
    
    // GameState access
    void Push(EGameState eGameState);
    void Pop(void);
    void Change(EGameState eGameState);

    GameState* GetCurrentGameState(void) const;

private:
    GameState* m_apGameState[e_game_state_max];
    EGameState m_eCurrentGameState;
    std::stack<GameState*> m_sGameState;
};

extern GameStateManager g_gameStateManager;