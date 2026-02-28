#ifndef HEXPIP_MENUSTATE_H
#define HEXPIP_MENUSTATE_H

#include "gameState.h"

class MenuState : public GameState {
public:
    MenuState() = default;
    ~MenuState() override = default;

    void OnEnter() override;
    void Update(float deltaTime) override;
    void Render(Graphics& graphics) override;
    void HandleInput() override;
};

#endif // HEXPIP_MENUSTATE_H