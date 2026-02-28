#include "gameStateMachine.h"

#include <iostream>
#include <stdexcept>
#include <chrono>

GameStateMachine::GameStateMachine(InputManager& inputManager)
    :m_inputManager(inputManager)
{
    m_randomManager.init(std::chrono::system_clock::now().time_since_epoch().count());
}


void GameStateMachine::RegisterState(const std::string& name, std::unique_ptr<GameState> state) {
    state->m_stateMachine = this;
    m_registeredStates[name] = std::move(state);
}

void GameStateMachine::PushState(const std::string& name) {
    const auto it = m_registeredStates.find(name);
    if (it == m_registeredStates.end()) {
        throw std::runtime_error("State not found: " + name);
    }

    if (!m_stateStack.empty()) {
        m_stateStack.top()->OnPause();
    }

    GameState* newState = it->second.get();
    m_stateStack.push(newState);
    newState->OnEnter();
}

void GameStateMachine::PopState() {
    if (m_stateStack.empty()) {
        return;
    }

    m_stateStack.top()->OnExit();
    m_stateStack.pop();

    if (!m_stateStack.empty()) {
        m_stateStack.top()->OnResume();
    }
}

bool GameStateMachine::PopToState(const std::string &name) {
    std::stack<GameState*> tmp = m_stateStack;
    bool found = false;

    while (!tmp.empty()) {
        const GameState* s = tmp.top();
        tmp.pop();

        if (const auto it = m_registeredStates.find(name); it != m_registeredStates.end() && s == it->second.get()) {
            found = true;
            break;
        }
    }

    if (!found) return false;

    const auto targetIt = m_registeredStates.find(name);
    const GameState* targetPtr = targetIt->second.get();

    while (!m_stateStack.empty() && m_stateStack.top() != targetPtr) {
        m_stateStack.top()->OnExit();
        m_stateStack.pop();
    }

    if (!m_stateStack.empty()) {
        m_stateStack.top()->OnResume();
        return true;
    }

    return false;
}

void GameStateMachine::ChangeState(const std::string& name) {
    if (!m_stateStack.empty()) {
        m_stateStack.top()->OnExit();
        m_stateStack.pop();
    }
    PushState(name);
}

void GameStateMachine::ClearStates() {
    while (!m_stateStack.empty()) {
        m_stateStack.top()->OnExit();
        m_stateStack.pop();
    }
}

void GameStateMachine::Update(const float deltaTime) {
    if (!m_stateStack.empty()) {
        m_stateStack.top()->Update(deltaTime);
    }
}

void GameStateMachine::Render(Graphics& graphics) {
    if (!m_stateStack.empty()) {
        m_stateStack.top()->Render(graphics);
    }
}

void GameStateMachine::HandleInput() {
    if (!m_stateStack.empty()) {
        m_stateStack.top()->HandleInput();
    }
}

GameState* GameStateMachine::GetCurrentState() const {
    if (m_stateStack.empty()) {
        return nullptr;
    }
    return m_stateStack.top();
}

InputManager& GameStateMachine::GetInputManager() const
{
    return m_inputManager;
}
