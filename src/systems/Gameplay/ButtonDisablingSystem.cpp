#include "ButtonDisablingSystem.h"
#include "core/Registry.h"
#include "component/UI/UIInteractable.h"
#include "component/Gameplay/Dice.h"
#include "component/Gameplay/Tags/ReRollButtonTag.h"
#include "component/Gameplay/Tags/EndRoundButtonTag.h"
#include "gameplay/HexPipRules.h"

void ButtonDisablingSystem(Registry& R, const bool reRoll) {
	R.forEach<ReRollButtonTag, UIInteractable>([&](Entity e, ReRollButtonTag&, UIInteractable& ui) {
		ui.enabled = reRoll;
	});

	std::vector<std::uint8_t> playingFaces;
	playingFaces.reserve(6);
	R.forEach<Dice>([&playingFaces](Entity e, const Dice& dice) {
		if (!dice.isBanked) playingFaces.push_back(dice.upperFace);
	});

	const bool endRound = !HasAnyScoringPlay(playingFaces) || reRoll;

	R.forEach<EndRoundButtonTag, UIInteractable>([&](Entity e, EndRoundButtonTag&, UIInteractable& ui) {
		ui.enabled = endRound;
	});
}
