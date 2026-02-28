#ifndef HEXPIP_PAUSEDSTATE_H
#define HEXPIP_PAUSEDSTATE_H

#include "gameState.h"

class PausedState : public GameState {
public:
    PausedState() = default;
    ~PausedState() override = default;

    void OnEnter() override;
    void Update(float deltaTime) override;
    void Render(Graphics& graphics) override;
    void HandleInput() override;
};

#endif // HEXPIP_PAUSEDSTATE_H