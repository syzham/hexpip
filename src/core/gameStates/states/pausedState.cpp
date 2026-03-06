#include "pausedState.h"

#include "systems/UI/InteractionSystem.h"
#include "systems/UI/ButtonSystem.h"
#include "systems/UI/RenderSpriteSystem.h"
#include "systems/UI/RenderTextSystem.h"
#include "systems/UI/ButtonSpriteSystem.h"

#include "core/gameStates/gameStateMachine.h"

void PausedState::OnEnter() {
    GameState::OnEnter();

    CreateButton("Resume Game", 0.5, 0.5, 0, -60, 160, 50, [&popRequested = m_popRequested] {
        popRequested = true;
    });

    CreateButton("Main Menu", 0.5, 0.5, 0, 0, 160, 50, [&popToStateRequest = m_popToStateRequest] {
        popToStateRequest = "Menu";
    });

    CreateButton("Quit Game", 0.5, 0.5, 0, 60, 160, 50, [&quitRequested = m_quitRequested] {
        quitRequested = true;
    });
}

void PausedState::Update(const float deltaTime) {
    if (m_stateMachine->GetInputManager().isKeyDown(53) || m_stateMachine->GetInputManager().isKeyDown(256)) {
        m_stateMachine->GetInputManager().setKeyDown(53, false);
        m_stateMachine->GetInputManager().setKeyDown(256, false);
        m_popRequested = true;
    }

    ButtonSpriteSystem(m_registry);

    GameState::Update(deltaTime);
}

void PausedState::Render(Graphics& graphics) {
    RenderSpriteSystem(m_registry, graphics);
    RenderTextSystem(m_registry, graphics);
}

void PausedState::HandleInput() {
    const auto inputMan = m_stateMachine->GetInputManager();
    InteractionSystem(
        m_registry,
        inputMan.getMouseX(),
        inputMan.getMouseY(),
        inputMan.isMouseDown(MouseButton::Mouse1)
        );
    ButtonSystem(m_registry);
}
