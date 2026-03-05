#include "core/gameStates/states/gameState.h"
#include "core/gameStates/gameStateMachine.h"
#include "component/UI/UIButton.h"
#include "component/UI/UITransform.h"
#include "component/UI/UIInteractable.h"
#include "component/UI/UIText.h"
#include "component/UI/UISprite.h"
#include "component/UI/UIButtonSprites.h"
#include "component/UI/UILayout.h"

#include "graphics/TextureLoader.h"
#include "core/Path.h"

void GameState::Update(float deltaTime) {
	if (!m_stateMachine) return;

	if (m_popRequested) {
		m_popRequested = false;
		m_stateMachine->PopState();
	}

	if (m_quitRequested) {
		m_quitRequested = false;
		m_stateMachine->ClearStates();
	}

	if (!m_pushStateRequest.empty()) {
		m_stateMachine->PushState(m_pushStateRequest);
		m_pushStateRequest = "";
	}

	if (!m_changeStateRequest.empty()) {
		m_stateMachine->ChangeState(m_changeStateRequest);
		m_changeStateRequest = "";
	}

	if (!m_popToStateRequest.empty()) {
		m_stateMachine->PopToState(m_popToStateRequest);
		m_popToStateRequest = "";
	}
}

void GameState::OnExit() {
	m_registry.clear();
}

void GameState::OnEnter() {}

void GameState::OnPause() {}

void GameState::OnResume() {}


uint32_t GameState::CreateButton(const std::string &text, float anchorX, float anchorY, float offsetX, float offsetY, float w, float h, const std::function<void()> &onClick) {
	const uint32_t button = m_registry.create();
	const GLuint hoverButton = TextureLoader::LoadTexture2D(Path::GetAssetPath("assets/ButtonPressed.png"));
	const GLuint idleButton = TextureLoader::LoadTexture2D(Path::GetAssetPath("assets/Button.png"));
	auto idle = UISprite{idleButton, 0, 0, 1, 1, 1, 1, 1, 1};
	const auto hover = UISprite{hoverButton, 0, 0, 1, 1, 1, 1, 1, 1};

	m_registry.emplace<UIButton>(button, UIButton{onClick});
	m_registry.emplace<UITransform>(button, UITransform{0, 0, w, h});
	m_registry.emplace<UIInteractable>(button, UIInteractable{});
	m_registry.emplace<UISprite>(button, idle);
	m_registry.emplace<UIButtonSprites>(button, UIButtonSprites{idle, hover});
	m_registry.emplace<UIText>(button, UIText{text, 0, 24});
	m_registry.emplace<UILayout>(button, UILayout{anchorX, anchorY, offsetX, offsetY});
	return button;
}
