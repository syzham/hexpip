#include "ScoringSystem.h"
#include "core/Registry.h"
#include "component/UI/UIText.h"
#include "component/Gameplay/Dice.h"
#include "component/Gameplay/Score.h"
#include "gameplay/HexPipRules.h"

void ScoringSystem(Registry& R) {
	R.forEach<Dice, UIText>([&](Entity e, const Dice& dice, UIText& txt) {
		txt.text = std::to_string(dice.upperFace);
	});

    std::vector<std::uint8_t> selectedFaces;
    selectedFaces.reserve(6);
	int currentTotal = 0;

	R.forEach<Dice>([&](Entity e, const Dice& dice) {
		if (!dice.isFinalised || !dice.isSelected) return;
	    selectedFaces.push_back(dice.upperFace);
	});

    const auto [points, validSelection] = ScoreDiceFaces(selectedFaces);
    currentTotal = validSelection ? points : 0;

	R.forEach<Score, UIText>([&currentTotal](Entity e, Score& score, UIText& txt) {
		score.currentScore = currentTotal;
	});
}
