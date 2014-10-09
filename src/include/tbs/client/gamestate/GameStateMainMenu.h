#pragma once

#include "GameState.h"

class GameStateMainMenu : public GameState {
public:

    explicit GameStateMainMenu(void);
    virtual ~GameStateMainMenu(void);

    virtual void Initialize(void);
    virtual void Release(void);
    virtual void Activate(void);
    virtual void DeActivate(void);

    virtual void Update(float dt);
    virtual void Render(void);

};