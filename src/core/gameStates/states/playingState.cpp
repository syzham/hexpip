#include "playingState.h"

#include "core/gameStates/gameStateMachine.h"

#include "component/UI/UIInteractable.h"
#include "component/UI/UIButton.h"
#include "component/UI/UIText.h"
#include "component/UI/UITransform.h"
#include "component/UI/UIDiceSprites.h"
#include "component/Gameplay/Score.h"
#include "component/Gameplay/Round.h"
#include "component/Gameplay/Dice.h"
#include "component/Gameplay/Tags/ReRollButtonTag.h"
#include "component/Gameplay/Tags/EndRoundButtonTag.h"

#include "systems/UI/PositionDiceSystem.h"
#include "systems/UI/RenderSpriteSystem.h"
#include "systems/UI/RenderTextSystem.h"
#include "systems/UI/ButtonSpriteSystem.h"
#include "systems/UI/InteractionSystem.h"
#include "systems/UI/ButtonSystem.h"
#include "systems/UI/DiceSpriteSystem.h"
#include "systems/Gameplay/DiceSystem.h"
#include "systems/Gameplay/ScoringSystem.h"
#include "systems/Gameplay/RerollSystem.h"
#include "systems/Gameplay/DiceSetSystem.h"
#include "systems/Gameplay/ButtonDisablingSystem.h"
#include "systems/Gameplay/EndRoundSystem.h"
#include "systems/Gameplay/UpdateTextSystem.h"

#include "graphics/TextureLoader.h"
#include "core/Path.h"

void PlayingState::OnEnter() {
    GameState::OnEnter();

    {
        const uint32_t score = m_registry.create();
        m_registry.emplace<UIText>(score, UIText{"", 0, 24, 1, 1, 1, 1, UIText::AlignH::Left});
        m_registry.emplace<UITransform>(score, UITransform{10, 10, 100, 50});
        m_registry.emplace<Score>(score, Score{});
    }

    {
        const uint32_t round = m_registry.create();
        m_registry.emplace<UIText>(round, UIText{"Round: ", 0, 24, 1, 1, 1, 1, UIText::AlignH::Left});
        m_registry.emplace<UITransform>(round, UITransform{10, 40, 100, 50});
        m_registry.emplace<Round>(round, Round{m_numberOfRounds});
    }

    for (int i = 0; i < m_numberOfDice; ++i) {
        CreateDice(0, 0);
    }

    CreateButton<EndRoundButtonTag>("End Round", 0.5, 1, -170, -100, 160, 50, [&] {
        EndRoundSystem(m_registry, m_hasDiceBanked, m_changeStateRequest, m_stateMachine->GetContext());
    }, EndRoundButtonTag{});

    CreateButton<ReRollButtonTag>("Reroll", 0.5, 1, 0, -100, 160, 50, [&] {
        RerollSystem(m_registry);
        m_hasDiceBanked = false;
    }, ReRollButtonTag{});

    CreateButton("Bank", 0.5, 1, 170, -100, 160, 50, [&] {
        DiceSetSystem(m_registry, m_hasDiceBanked);
    });
}

void PlayingState::Update(const float deltaTime) {
    if (m_stateMachine->GetInputManager().isKeyDown(53)) {
        m_stateMachine->GetInputManager().setKeyDown(53, false);
        m_pushStateRequest = "Paused";
    }

    DiceSpriteSystem(m_registry);
    ButtonDisablingSystem(m_registry, m_hasDiceBanked);
    ButtonSpriteSystem(m_registry);
    DiceSystem(m_registry, m_stateMachine->GetRandomManager());
    ScoringSystem(m_registry);
    UpdateTextSystem(m_registry);

    GameState::Update(deltaTime);
}

void PlayingState::Render(Graphics& graphics) {
    PositionDiceSystem(m_registry, graphics, m_numberOfDice);
    RenderSpriteSystem(m_registry, graphics);
    RenderTextSystem(m_registry, graphics);
}

void PlayingState::HandleInput() {
    const auto inputMan = m_stateMachine->GetInputManager();
    InteractionSystem(
        m_registry,
        inputMan.getMouseX(),
        inputMan.getMouseY(),
        inputMan.isMouseDown(MouseButton::Mouse1)
        );
    ButtonSystem(m_registry);
}

void PlayingState::CreateDice(const float x, const float y) {
    const uint32_t dice = m_registry.create();
    UIButton btn{};
    btn.onClick = [&reg = m_registry, dice] {
        if (!reg.has<Dice>(dice)) return;
        auto &die = reg.get<Dice>(dice);
        die.isSelected = !die.isSelected;

    };

    const GLuint one = TextureLoader::LoadTexture2D(Path::GetAssetPath("assets/One.png"));
    const GLuint two = TextureLoader::LoadTexture2D(Path::GetAssetPath("assets/Two.png"));
    const GLuint three = TextureLoader::LoadTexture2D(Path::GetAssetPath("assets/Three.png"));
    const GLuint four = TextureLoader::LoadTexture2D(Path::GetAssetPath("assets/Four.png"));
    const GLuint five = TextureLoader::LoadTexture2D(Path::GetAssetPath("assets/Five.png"));
    const GLuint six = TextureLoader::LoadTexture2D(Path::GetAssetPath("assets/Six.png"));
    auto oneSprite = UISprite{one, 0, 0, 1, 1, 1, 1, 1, 1};
    auto twoSprite = UISprite{two, 0, 0, 1, 1, 1, 1, 1, 1};
    auto threeSprite = UISprite{three, 0, 0, 1, 1, 1, 1, 1, 1};
    auto fourSprite = UISprite{four, 0, 0, 1, 1, 1, 1, 1, 1};
    auto fiveSprite = UISprite{five, 0, 0, 1, 1, 1, 1, 1, 1};
    auto sixSprite = UISprite{six, 0, 0, 1, 1, 1, 1, 1, 1};

    m_registry.emplace<UIButton>(dice, std::move(btn));
    m_registry.emplace<UITransform>(dice, UITransform{x, y, 100, 100});
    m_registry.emplace<UIDiceSprites>(dice, UIDiceSprites{oneSprite, twoSprite, threeSprite, fourSprite, fiveSprite, sixSprite});
    m_registry.emplace<UIInteractable>(dice, UIInteractable{});
    m_registry.emplace<UISprite>(dice, oneSprite);
    m_registry.emplace<Dice>(dice, Dice{});
}