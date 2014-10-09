#include "client/gamestate/GameStateManager.h"
#include "client/gamestate/GameStateMainMenu.h"

GameStateManager g_gameStateManager;

GameStateManager::GameStateManager(void)
: m_eCurrentGameState(e_game_state_main_menu)
, m_sGameState() {

}

GameStateManager::~GameStateManager(void) {

}

void GameStateManager::Initialize(void) {
    m_apGameState[e_game_state_main_menu] = new GameStateMainMenu();

    m_apGameState[e_game_state_main_menu]->Initialize();

    m_eCurrentGameState = e_game_state_main_menu;
    Push(m_eCurrentGameState);
}

void GameStateManager::Release(void) {
    for (int eGameState = 0; eGameState < e_game_state_max; ++eGameState) {
        delete(m_apGameState[eGameState]);
    }

    while (!m_sGameState.empty()) {
        m_sGameState.pop();
    }
}

void GameStateManager::UpdateAndRender(float dt) {
    GameState* pCurrentGameState = GetCurrentGameState();

    if (nullptr != pCurrentGameState) {
        pCurrentGameState->Update(dt);
        pCurrentGameState->Render();
    }
}

void GameStateManager::Push(EGameState eGameState) {
    GameState* pCurrentGameState = GetCurrentGameState();

    if (nullptr != pCurrentGameState) {
        pCurrentGameState->DeActivate();
    }

    m_apGameState[eGameState]->Activate();
    m_eCurrentGameState = eGameState;

    m_sGameState.push(m_apGameState[eGameState]);
}

void GameStateManager::Pop(void) {
    GameState* pCurrentGameState = GetCurrentGameState();

    if (nullptr != pCurrentGameState) {
        m_sGameState.pop();
    }

    GetCurrentGameState()->Activate();
}

void GameStateManager::Change(EGameState eGameState) {
    //pop
    GameState* pCurrentGameState = GetCurrentGameState();

    if (nullptr != pCurrentGameState) {
        pCurrentGameState->DeActivate();
    }

    m_sGameState.pop();

    //push
    m_apGameState[eGameState]->Activate();
    m_eCurrentGameState = eGameState;

    m_sGameState.push(m_apGameState[eGameState]);
}

GameState * GameStateManager::GetCurrentGameState(void) const {
    if (m_sGameState.empty()) {
        return (nullptr);
    }

    return (m_sGameState.top());
}