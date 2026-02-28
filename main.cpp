#include "window/Window.h"
#include "src/core/gameStates/gameStateMachine.h"
#include "src/core/gameStates/states/menuState.h"
#include "src/core/gameStates/states/playingState.h"
#include "src/core/gameStates/states/pausedState.h"
#include "src/core/gameStates/states/gameOverState.h"

int winW = 800, winH = 600;

int main() {
    auto inputManager = InputManager();
    auto window = Window(winW, winH, "Hex & Pips", inputManager);
    auto stateMachine = GameStateMachine(inputManager);
    int fail = window.InitWindow();

    if (fail)
      return 1;

    stateMachine.RegisterState("Menu", std::make_unique<MenuState>());
    stateMachine.RegisterState("Playing", std::make_unique<PlayingState>());
    stateMachine.RegisterState("Paused", std::make_unique<PausedState>());
	stateMachine.RegisterState("GameOver", std::make_unique<GameOverState>());

    stateMachine.PushState("Menu");

    float deltaTime = 0.016f;

    while (window.IsRunning() && stateMachine.HasStates()) {
        stateMachine.HandleInput();
        stateMachine.Update(deltaTime);
        
        window.BeginFrame();
        stateMachine.Render(window.GetGraphics());
        window.EndFrame();
    }

    stateMachine.ClearStates();
    window.DestroyWindow();
    return 0;
}
