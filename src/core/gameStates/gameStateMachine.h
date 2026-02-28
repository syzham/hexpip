#ifndef HEXPIP_GAMESTATEMACHINE_H
#define HEXPIP_GAMESTATEMACHINE_H

#include <memory>
#include <stack>
#include <unordered_map>
#include <string>
#include "states/gameState.h"
#include "core/InputManager.h"
#include "core/gameContext.h"
#include "core/RandomManager.h"

class GameStateMachine {
public:
	explicit GameStateMachine(InputManager &inputManager);

	~GameStateMachine() = default;

	void RegisterState(const std::string &name, std::unique_ptr<GameState> state);

	void PushState(const std::string &name);

	void PopState();

	bool PopToState(const std::string &name);

	void ChangeState(const std::string &name);

	void ClearStates();

	void Update(float deltaTime);

	void Render(Graphics &graphics);

	void HandleInput();

	[[nodiscard]] bool HasStates() const { return !m_stateStack.empty(); }

	[[nodiscard]] GameState *GetCurrentState() const;

	[[nodiscard]] InputManager &GetInputManager() const;

	GameContext &GetContext() { return m_context; }
	RandomManager &GetRandomManager() { return m_randomManager; }

private:
	std::unordered_map<std::string, std::unique_ptr<GameState> > m_registeredStates;
	std::stack<GameState *> m_stateStack;
	InputManager &m_inputManager;
	GameContext m_context;
	RandomManager m_randomManager;
};

#endif // HEXPIP_GAMESTATEMACHINE_H