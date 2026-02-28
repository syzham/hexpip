#ifndef HEXPIP_UPGRADES_H
#define HEXPIP_UPGRADES_H
#include <cstdint>

using UpgradeID = uint16_t;

enum class Upgrade : UpgradeID {
	PairedUp, // Any pair can be rerolled
};

struct UpgradeState {
	uint8_t level = 0;
	uint8_t stack = 0;
	int price = 0;
};

#endif //HEXPIP_UPGRADES_H