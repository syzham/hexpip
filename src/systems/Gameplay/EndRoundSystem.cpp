#include "EndRoundSystem.h"
#include "core/Registry.h"
#include "component/UI/UIInteractable.h"
#include "component/Gameplay/Dice.h"
#include "component/Gameplay/Score.h"
#include "component/Gameplay/Round.h"
#include "core/gameContext.h"

void EndRoundSystem(Registry& R, const bool hasDiceBanked, std::string& changeStateRequest, GameContext& gameContext) {
	R.forEach<Round>([&](Entity e, Round& round) {
		round.roundNumber--;
		if (round.roundNumber <= 0) changeStateRequest = "GameOver";
	});

	R.forEach<Dice, UIInteractable>([&](Entity e, Dice& dice, UIInteractable& ui) {
		dice.isBanked = false;
		dice.isSelected = false;
		dice.isFinalised = false;
		ui.enabled = true;
	});

	R.forEach<Score>([&](Entity e, Score& score) {
		if (hasDiceBanked)
			score.totalScore += score.roundScore;
		score.roundScore = 0;
		gameContext.finalScore = score.totalScore;
	});
}
