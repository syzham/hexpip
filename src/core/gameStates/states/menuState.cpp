#include "menuState.h"
#include "systems/UI/InteractionSystem.h"
#include "systems/UI/ButtonSystem.h"
#include "systems/UI/RenderSpriteSystem.h"
#include "systems/UI/RenderTextSystem.h"
#include "systems/UI/ButtonSpriteSystem.h"

#include "core/gameStates/gameStateMachine.h"

void MenuState::OnEnter() {
    GameState::OnEnter();

    CreateButton("Start Game", 0.5, 1, 0, -160, 160, 50, [&pushRequest = m_pushStateRequest] {
        pushRequest = "Playing";
    });

    CreateButton("Quit Game", 0.5, 1, 0, -100, 160, 50, [&quitRequested = m_quitRequested] {
        quitRequested = true;
    });
}

void MenuState::Update(const float deltaTime) {
    ButtonSpriteSystem(m_registry);
    GameState::Update(deltaTime);
}

void MenuState::Render(Graphics& graphics) {
    RenderSpriteSystem(m_registry, graphics);
    RenderTextSystem(m_registry, graphics);
}

void MenuState::HandleInput() {
  const auto inputMan = m_stateMachine->GetInputManager();
  InteractionSystem(
      m_registry,
      inputMan.getMouseX(), 
      inputMan.getMouseY(), 
      inputMan.isMouseDown(MouseButton::Mouse1)
      );
  ButtonSystem(m_registry);
}
