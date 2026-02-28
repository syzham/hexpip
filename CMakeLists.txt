cmake_minimum_required(VERSION 4.0)
project(HexPip)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(glfw
  GIT_REPOSITORY https://github.com/glfw/glfw.git
  GIT_TAG 3.3.9)
FetchContent_MakeAvailable(glfw)

find_package(OpenGL REQUIRED)

add_executable(HexPip main.cpp external/glad/glad.c
        src/Window/window.cpp
        src/Window/window.h
        src/graphics/graphics.cpp
        src/graphics/graphics.h
        src/core/event/Event.h
        src/core/event/MouseEvent.h
        src/core/InputManager.cpp
        src/core/InputManager.h
        src/core/GameStates/gameStateMachine.cpp
        src/core/gameStates/states/menuState.cpp
        src/core/gameStates/states/playingState.cpp
        src/core/gameStates/states/pausedState.cpp
        src/component/UI/UITransform.h
        src/component/UI/UISprite.h
        src/component/UI/UIButton.h
        src/component/UI/UIInteractable.h
        src/core/Registry.h
        src/core/Registry.cpp
        external/stb/stb_image.h
        src/graphics/TextureLoader.cpp
        src/graphics/TextureLoader.h
        external/stb/stb_truetype.h
        src/component/UI/UIText.h
        src/graphics/FontAtlas.cpp
        src/graphics/FontAtlas.h
        src/core/gameStates/states/gameState.cpp
        src/component/Gameplay/Dice.h
        src/systems/Gameplay/DiceSystem.cpp
        src/systems/Gameplay/ScoringSystem.cpp
        src/systems/Gameplay/RerollSystem.cpp
        src/component/Gameplay/Score.h
        external/doctest/doctest.h
        src/systems/UI/PositionDiceSystem.cpp
        src/systems/Gameplay/DiceSetSystem.cpp
        src/component/UI/UILayout.h
        src/component/Gameplay/Tags/ReRollButtonTag.h
        src/systems/Gameplay/ButtonDisablingSystem.cpp
        src/systems/Gameplay/EndRoundSystem.cpp
        src/component/Gameplay/Tags/EndRoundButtonTag.h
        src/component/Gameplay/Round.h
        src/systems/Gameplay/UpdateTextSystem.cpp
        src/core/gameStates/states/gameOverState.h
        src/core/gameStates/states/gameOverState.cpp
        src/core/gameContext.h
        src/core/upgrades.h
        src/core/upgrades.h
        src/systems/Gameplay/ButtonDisablingSystem.h
        src/systems/Gameplay/DiceSetSystem.h
        src/systems/Gameplay/DiceSystem.h
        src/systems/Gameplay/EndRoundSystem.h
        src/systems/Gameplay/RerollSystem.h
        src/systems/Gameplay/ScoringSystem.h
        src/systems/Gameplay/UpdateTextSystem.h
        src/systems/UI/ButtonSpriteSystem.h
        src/systems/UI/ButtonSpriteSystem.cpp
        src/systems/UI/ButtonSystem.h
        src/systems/UI/ButtonSystem.cpp
        src/systems/UI/InteractionSystem.h
        src/systems/UI/InteractionSystem.cpp
        src/systems/UI/PositionDiceSystem.h
        src/systems/UI/RenderSpriteSystem.h
        src/systems/UI/RenderSpriteSystem.cpp
        src/systems/UI/RenderTextSystem.h
        src/systems/UI/RenderTextSystem.cpp
        src/core/RandomManager.cpp
        src/core/RandomManager.h
        src/gameplay/HexPipRules.cpp
        src/gameplay/HexPipRules.h
        src/component/UI/UIDiceSprites.h
        src/systems/UI/DiceSpriteSystem.cpp
        src/systems/UI/DiceSpriteSystem.h
        src/core/gameStates/gameStateMachine.h
        src/core/gameStates/states/playingState.h
        src/core/gameStates/states/pausedState.h
        src/core/gameStates/states/menuState.h
        src/component/UI/UIButtonSprites.h
)

target_include_directories(HexPip PRIVATE ${CMAKE_SOURCE_DIR}/external ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(HexPip PRIVATE glfw OpenGL::GL)

add_custom_command(TARGET HexPip POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets
        $<TARGET_FILE_DIR:HexPip>/assets
        COMMENT "Copying assets to runtime output directory"
)

include(CTest)
enable_testing()

add_executable(HexPipTests
        tests/test_main.cpp
        tests/test_scoring.cpp
        src/gameplay/HexPipRules.h
        src/gameplay/HexPipRules.cpp
        tests/test_possibleMoves.cpp
)

target_include_directories(HexPipTests PRIVATE
        ${CMAKE_SOURCE_DIR}/external
        ${CMAKE_SOURCE_DIR}/src
)

add_test(NAME HexPipTests COMMAND HexPipTests)