#include "gameOverState.h"

#include "component/UI/UILayout.h"
#include "component/UI/UIText.h"
#include "component/UI/UITransform.h"

#include "systems/UI/InteractionSystem.h"
#include "systems/UI/ButtonSystem.h"
#include "systems/UI/RenderSpriteSystem.h"
#include "systems/UI/RenderTextSystem.h"
#include "systems/UI/ButtonSpriteSystem.h"

#include "core/gameStates/gameStateMachine.h"

void GameOverState::OnEnter() {
    GameState::OnEnter();

    {
        const uint32_t score = m_registry.create();
        m_registry.emplace<UIText>(score, UIText{ "Game Over\nTotal Score :"+std::to_string(m_stateMachine->GetContext().finalScore), 0, 24, 1, 1, 1, 1});
        m_registry.emplace<UITransform>(score, UITransform{0, 0, 100, 50});
        m_registry.emplace<UILayout>(score, UILayout{0.5, 0.5, 0, 0});
    }

    CreateButton("Restart Game", 0.5, 1, 0, -220, 160, 50, [&changeStateRequest = m_changeStateRequest] {
        changeStateRequest = "Playing";
    });

    CreateButton("Main Menu", 0.5, 1, 0, -160, 160, 50, [&popToStateRequest = m_popToStateRequest] {
        popToStateRequest = "Menu";
    });

    CreateButton("Quit Game", 0.5, 1, 0, -100, 160, 50, [&quitRequested = m_quitRequested] {
        quitRequested = true;
    });
}

void GameOverState::Update(const float deltaTime) {
    if (m_stateMachine->GetInputManager().isKeyDown(53)) {
        m_stateMachine->GetInputManager().setKeyDown(53, false);
        m_popRequested = true;
    }

    ButtonSpriteSystem(m_registry);

    GameState::Update(deltaTime);
}

void GameOverState::Render(Graphics& graphics) {
    RenderSpriteSystem(m_registry, graphics);
    RenderTextSystem(m_registry, graphics);
}

void GameOverState::HandleInput() {
    const auto inputMan = m_stateMachine->GetInputManager();
    InteractionSystem(
        m_registry,
        inputMan.getMouseX(),
        inputMan.getMouseY(),
        inputMan.isMouseDown(MouseButton::Mouse1)
        );
    ButtonSystem(m_registry);
}
