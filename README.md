<div align="center">
    <img src="https://github-readme-tech-stack.vercel.app/api/cards?title=Hex+%26+Pip&align=center&titleAlign=center&lineCount=1&bg=%230D1117&badge=%23161B22&border=%2321262D&titleColor=%2358A6FF&line1=cplusplus%2CC%2B%2B20%2C00599C%3Bcmake%2CCMake%2C064F8C%3Bopengl%2COpenGL%2C5586A4%3B" alt="Hex & Pip" />
</div>

A single-player roguelike dice game based on the folk game "Farkle."

This project is from scratch built around:
- OpenGL rendering
- ECS-style architecture (custom registry/components)
- Game state machine (Menu/Playing/Paused)
- Test Driven Development (TDD) as systems and gameplay expand

## Gameplay

At the start of the game, six dice are rolled. The player must create combos to score points.  
Points are as follows:
- 1: 100 points
- 5: 50 points
- three of a kind: 100 * value of the dice
- four of a kind: 1,000 points
- five of a kind: 2,000 points
- six of a kind: 3,000 points
- Straight (1–6): 1,500 points
- Three pairs: 1,500 points
- Four of a kind and pair: 1,500 points
- Two Triplets: 2,500 points

After selecting a combo, the player can bank the dice and either roll the remaining dice or end the current round.  
If all six dice are banked, the player gains 5,000 points and gets to roll the dice again.  
  
If the player rolls and there are no valid combos to play, the player looses all of their points for that round.  
The player must accumulate a total that exceeds the final needed score before all the rounds are finished.  
If the player manages to accumulate the final score, they can spend their points on upgrades.

## Goals

- Cross-platform: Windows/Mac/Linux
- Minimal external libraries (only what’s necessary)
- Clean architecture:
  - ECS for gameplay + UI entities
  - explicit state transitions via a stack-based state machine
- Test Driven Development:
  - scoring logic
  - upgrade interactions
  - roll evaluation

## Build & Run

### Prerequisites:
- A C++20 compiler
  - **Windows**: MSVC
  - **macOS**: AppleClang
  - **Linux**: GCC/Clang
- CMake

### Build Types
- **Debug**: Includes debug symbols, shows console window for debugging output
- **Release**: Optimized, no console window (Windows/macOS only)
- **RelWithDebInfo**: Optimized with debug info, no console window
- **MinSizeRel**: Size-optimized

### Using Build Scripts (Recommended)

**macOS/Linux:**
```bash
# Debug build and run
./build.sh Debug --run

# Release build
./build.sh Release

# Run tests
./build.sh Debug --test

# Clean build
./build.sh Debug --clean
```

**Windows (Command Prompt):**
```cmd
REM Debug build and run
build.bat Debug --run

REM Release build
build.bat Release

REM Run tests
build.bat Debug --test

REM Clean build
build.bat Debug --clean
```

**Windows (PowerShell):**
```powershell
# Debug build and run
pwsh .\build.ps1 -Run

# Release build
pwsh .\build.ps1 -Config Release

# Run tests
pwsh .\build.ps1 -Test

# Clean build
pwsh .\build.ps1 -Clean
```

### Manual Build (CLI)

From the project root:
```bash
cmake -S . -B build/Debug -DCMAKE_BUILD_TYPE=Debug
cmake --build build/Debug --parallel
```

Run the executable:
```bash
# Debug build (all platforms)
./build/Debug/HexPip              # macOS/Linux
build\Debug\HexPip.exe            # Windows

# Release build
./build/Release/HexPip            # Linux
open build/Release/HexPip.app     # macOS (creates .app bundle)
build\Release\HexPip.exe          # Windows
```
