#include "DiceSystem.h"
#include "core/Registry.h"
#include "component/Gameplay/Dice.h"
#include "core/RandomManager.h"

void DiceSystem(Registry& R, RandomManager& random) {
	R.forEach<Dice>([&](Entity e, Dice& dice) {
		if (dice.isFinalised) return;
		dice.upperFace = random.getRandomNumber(1, 6);
		dice.isFinalised = true;
	});

}
