#ifndef HEXPIP_HEXPIPRULES_H
#define HEXPIP_HEXPIPRULES_H

#include <vector>

using diceCount = std::array<int, 7>;
using diceList = std::vector<std::uint8_t>;

struct HexPipScoreResult {
	int points = 0;
	bool validSelection = false;
};

diceCount countFaces(const diceList& faces);

HexPipScoreResult ScoreDiceFaces(const diceList& faces);

int countPairs(const diceCount& faces, int amount);

bool isStraight(const diceCount& faces);

bool HasAnyScoringPlay(const diceList& faces);

#endif //HEXPIP_HEXPIPRULES_H