#ifndef HEXPIP_GAMEOVERSTATE_H
#define HEXPIP_GAMEOVERSTATE_H

#include "gameState.h"

class GameOverState : public GameState {
public:
    GameOverState() = default;
    ~GameOverState() override = default;

    void OnEnter() override;
    void Update(float deltaTime) override;
    void Render(Graphics& graphics) override;
    void HandleInput() override;
};

#endif // HEXPIP_GAMEOVERSTATE_H