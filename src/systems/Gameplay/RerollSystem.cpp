#include "RerollSystem.h"
#include "core/Registry.h"
#include "component/Gameplay/Dice.h"

void RerollSystem(Registry& R) {
	R.forEach<Dice>([&](Entity e, Dice& dice) {
		if (dice.isBanked) return;

		dice.isFinalised = false;
		dice.isSelected = false;
	});
}
