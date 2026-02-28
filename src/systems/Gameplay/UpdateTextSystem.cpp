#include "UpdateTextSystem.h"
#include "core/Registry.h"
#include "component/UI/UIText.h"
#include "component/Gameplay/Score.h"
#include "component/Gameplay/Round.h"

void UpdateTextSystem(Registry& R) {
	R.forEach<UIText, Score>([](Entity e, UIText& text, const Score& score) {
		text.text = "Score: " + std::to_string(score.totalScore + score.roundScore);
		if (score.currentScore != 0) text.text.append("  +" + std::to_string(score.currentScore));
	});
	R.forEach<UIText, Round>([](Entity e, UIText& text, const Round& round) {
		text.text = "Round: " + std::to_string(round.roundNumber);
	});
}