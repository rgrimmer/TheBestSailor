#pragma once

class GameState {
public:

    explicit GameState(void);
    virtual ~GameState(void);

    virtual void Initialize(void) = 0;
    virtual void Release(void) = 0;
    virtual void Activate(void) = 0;
    virtual void DeActivate(void) = 0;

    virtual void Update(float dt) = 0;
    virtual void Render(void) = 0;

};