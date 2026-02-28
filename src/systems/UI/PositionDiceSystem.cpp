#include "PositionDiceSystem.h"
#include "core/Registry.h"
#include "graphics/Graphics.h"
#include "component/Gameplay/Dice.h"
#include "component/UI/UITransform.h"
#include "component/UI/UIInteractable.h"


void PositionDiceSystem(Registry& R, Graphics& graphics, const int numberOfDice) {

	int diceLeft = numberOfDice;
	R.forEach<Dice>([&](Entity e, const Dice& dice) {
		if (!dice.isBanked) return;
		diceLeft--;
	});

	R.forEach<Dice, UIInteractable>([&](Entity e, Dice& dice, const UIInteractable& ui) {
		if (ui.state == UIInteractState::Hovered && !dice.isHovered) {
			dice.isHovered = true;
		} else if (ui.state == UIInteractState::Idle && dice.isHovered) {
			dice.isHovered = false;
		}
	});

	const float totalLength = (static_cast<float>(diceLeft) * diceWidth) + (dicePadding * static_cast<float>(diceLeft - 1));

	int playingDiceIndex = 0;
	int bankedDiceIndex = 0;
	R.forEach<Dice, UITransform>([&](Entity e, const Dice& dice, UITransform& trans) {
		if (dice.isBanked) {
			trans.height = 50;
			trans.width = 50;
			trans.x = static_cast<float>(graphics.getWidth()) - 50 - dicePadding;
			trans.y = playingDiceY + (50 + dicePadding) * static_cast<float>(bankedDiceIndex++);
			return;
		}

		trans.height = diceHeight;
		trans.width = diceWidth;

		trans.y = dice.isSelected ? playingDiceY - (diceHeight / 3) : dice.isHovered ? playingDiceY - (diceHeight / 4) : playingDiceY;
		trans.x = ((static_cast<float>(graphics.getWidth()) / 2) - (totalLength / 2)) + ((diceWidth + dicePadding) * static_cast<float>(playingDiceIndex++));
	});
}