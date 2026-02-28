#include "DiceSetSystem.h"
#include "core/Registry.h"
#include "component/UI/UIInteractable.h"
#include "component/Gameplay/Dice.h"
#include "component/Gameplay/Score.h"

void DiceSetSystem(Registry& R, bool& isBanked) {
	bool diceLeft = false;
	R.forEach<Dice>([&](Entity e, const Dice& dice) {
		if (!dice.isBanked && !dice.isSelected) {
			diceLeft = true;
		}
	});

	int currentScore = 0;
	R.forEach<Score>([&](Entity e, Score& score) {
		if (!diceLeft) score.currentScore += 5000;
		score.roundScore += score.currentScore;
		currentScore += score.currentScore;
	});


	if (currentScore <= 0) return;


	R.forEach<Dice, UIInteractable>([&](Entity e, Dice& dice, UIInteractable& ui) {
		if (dice.isSelected && diceLeft) {
			dice.isBanked = true;
			isBanked = true;
			dice.isSelected = false;
			ui.enabled = false;
		} else if (!diceLeft) {
			dice.isBanked = false;
			isBanked = true;
			dice.isSelected = false;
			ui.enabled = true;
			dice.isFinalised = false;
		}
	});
}