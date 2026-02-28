#ifndef HEXPIP_PLAYINGSTATE_H
#define HEXPIP_PLAYINGSTATE_H

#include "gameState.h"

class PlayingState : public GameState {
public:
    PlayingState() = default;
    ~PlayingState() override = default;

    void OnEnter() override;
    void Update(float deltaTime) override;
    void Render(Graphics& graphics) override;
    void HandleInput() override;

private:
    void CreateDice(float x, float y);

    uint8_t m_numberOfDice = 6;
    uint8_t m_numberOfRounds = 6;
    bool m_hasDiceBanked = false;
};

#endif // HEXPIP_PLAYINGSTATE_H