#ifndef HEXPIP_DICE_H
#define HEXPIP_DICE_H
#include <cstdint>

struct Dice {
	uint8_t upperFace = 1;
	bool isFinalised = false;
	bool isSelected = false;
	bool isHovered = false;
	bool isBanked = false;
};

#endif //HEXPIP_DICE_H