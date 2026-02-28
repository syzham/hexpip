# Hex & Pips

---
A single-player roguelike dice game based on the folk game "Farkle."

This project is from scratch built around:
- OpenGL rendering
- ECS-style architecture (custom registry/components)
- Game state machine (Menu/Playing/Paused)
- Test Driven Development (TDD) as systems and gameplay expand

## Gameplay

---
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

---
- Cross-platform: Windows/Mac/Linux
- Minimal external libraries (only what’s necessary)
- Clean architecture:
  - ECS for gameplay + UI entities
  - explicit state transitions via a stack-based state machine
- Test Driven Development:
  - scoring logic
  - upgrade interactions
  - roll evaluation

## Tech Stack

---
- **Language**: C++20
- **Build**: CMake
- **Window/Input**: GLFW
- **OpenGL loader**: glad (vendored)
- **Rendering**: OpenGL 3.3 core profile
- **Architecture**: ECS+TDD

## Build & Run

---
### Prerequisites:
- A C++20 compiler
  - **Windows**: MSVC
  - **macOS**: AppleClang
  - **Linux**: GCC/Clang
- CMake

### Build (CLI)

From the project root:
```bash
cmake -S . -B build
cmake --build build -j
```
Run:
```bash
./build/HexPip
```
