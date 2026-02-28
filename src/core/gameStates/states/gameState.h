#ifndef HEXPIP_GAMESTATE_H
#define HEXPIP_GAMESTATE_H

#include <functional>

#include "core/Registry.h"

class GameStateMachine;
class Graphics;

class GameState {
public:
    virtual ~GameState() = default;

    virtual void OnEnter();
    virtual void OnExit();
    virtual void OnPause();
    virtual void OnResume();
    virtual void Update(float deltaTime);
    virtual void Render(Graphics& graphics) = 0;
    virtual void HandleInput() = 0;

    uint32_t CreateButton(const std::string &text, float anchorX, float anchorY, float offsetX, float offsetY, float w, float h, const std::function<void()> &onClick);

    template <typename... Tags>
    uint32_t CreateButton(const std::string &text, float anchorX, float anchorY, float offsetX, float offsetY, float w, float h, const std::function<void()> &onClick, Tags&&... tags) {
        const uint32_t button = CreateButton(text, anchorX, anchorY, offsetX, offsetY, w, h, onClick);
        (m_registry.emplace<Tags>(button, std::forward<Tags>(tags)), ...);
        return button;
    }

protected:
    GameStateMachine* m_stateMachine = nullptr;
    friend class GameStateMachine;
    Registry m_registry;

    bool m_popRequested = false;
    bool m_quitRequested = false;
    std::string m_changeStateRequest;
    std::string m_pushStateRequest;
    std::string m_popToStateRequest;
};

#endif // HEXPIP_GAMESTATE_H