#ifndef HEXPIP_GAMECONTEXT_H
#define HEXPIP_GAMECONTEXT_H

#include <array>
#include "core/upgrades.h"

constexpr size_t maxUpgrades = 64;

struct GameContext {
	int finalScore = 0;

	std::array<UpgradeState, maxUpgrades> upgrades;

	UpgradeState& GetUpgrade(const Upgrade upgrade) { return upgrades[static_cast<UpgradeID>(upgrade)]; }
};

#endif //HEXPIP_GAMECONTEXT_H