#ifndef HEXPIP_ENDROUNDSYSTEM_H
#define HEXPIP_ENDROUNDSYSTEM_H

#include <iosfwd>

class Registry;
struct GameContext;

void EndRoundSystem(Registry& R, bool hasDiceBanked, std::string& changeStateRequest, GameContext& gameContext);

#endif //HEXPIP_ENDROUNDSYSTEM_H