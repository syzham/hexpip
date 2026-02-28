#include "HexPipRules.h"

diceCount countFaces(const diceList& faces) {
	diceCount count{};
	for (const auto face : faces) {
		if (face < 1 || face > 6) continue;
		count[face]++;
	}
	return count;
}

int countPairs(const diceCount &faces, const int amount) {
	int pairs = 0;
	for (int face = 1; face <= 6; ++face) {
		if (faces[face] == amount)
			pairs++;
	}
	return pairs;
}

bool isStraight(const diceCount& faces) {
	return faces[1]==1 && faces[2]==1 && faces[3]==1 && faces[4]==1 && faces[5]==1 && faces[6]==1;
}

HexPipScoreResult ScoreDiceFaces(const diceList& faces)
{
	HexPipScoreResult final{};

	if (faces.empty()) {
		final.points = 0;
		final.validSelection = true;
		return final;
	}

	diceCount count = countFaces(faces);

	const int pairs = countPairs(count, 2);
	const int triplets = countPairs(count, 3);
	const int quads = countPairs(count, 4);
	const int quint = countPairs(count, 5);
	const int six = countPairs(count, 6);

	int points = 0;

	if (isStraight(count)) {
		points += 1500;
		count[1] = 0;
		count[2] = 0;
		count[3] = 0;
		count[4] = 0;
		count[5] = 0;
		count[6] = 0;
	}
	if (pairs == 3) {
		points += 1500;
		int i = 3;
		for (int f = 1; f <= 6 && i > 0; ++f) {if (count[f]==2) {count[f] = 0;i--;}}
	}
	if (quads == 1 && pairs == 1) {
		points += 1500;
		bool removedQuad = false;
		bool removedPair = false;
		for (int f = 1; f <= 6; ++f) {
			if (removedQuad && removedPair) break;
			if (count[f]==4 && !removedQuad) {
				count[f] = 0;
				removedQuad = true;
			}
			if (count[f]==2 && !removedPair) {
				count[f] = 0;
				removedPair = true;
			}
		}
	}
	if (quads == 1 && pairs == 0) {
		points += 1000;
		for (int f = 1; f <= 6; ++f) { if (count[f]==4) { count[f] = 0; break; }}
	}
	if (quint == 1) {
		points += 2000;
		for (int f = 1; f <= 6; ++f) {if (count[f]==5) {count[f] = 0;break;}}
	}
	if (triplets == 2) {
		points += 2500;
		int i = 2;
		for (int f = 1; f <= 6 && i > 0; ++f) {if (count[f]==3) {count[f] = 0;i--;}}

	}
	if (six == 1) {
		points += 3000;
		for (int f = 1; f <= 6; ++f) {if (count[f]==6) {count[f] = 0;break;}}
	}


	for (int f = 1; f <= 6; ++f) {
		if (count[f] == 3) {
			const int base = (f == 1) ? 1000 : (f * 100);
			points += base;
			count[f] = 0;
		}
	}

	points += count[1] * 100;
	count[1] = 0;
	points += count[5] * 50;
	count[5] = 0;

	for (int f = 1; f <= 6; ++f) {
		if (count[f] > 0) {
			points = 0;
			break;
		}
	}

	final.points = points;
	final.validSelection = points > 0;
	return final;
}

bool HasAnyScoringPlay(const diceList& faces)
{
	const diceCount count = countFaces(faces);

	if (count[1] > 0) return true;
	if (count[5] > 0) return true;

	const int pairs = countPairs(count, 2);
	const int triplets = countPairs(count, 3);
	const int quads = countPairs(count, 4);
	const int quint = countPairs(count, 5);
	const int six = countPairs(count, 6);

	if (triplets >= 1) return true;
	if (quads >= 1) return true;
	if (quint >= 1) return true;
	if (six >= 1) return true;

	if (isStraight(count)) return true;

	if (pairs >= 3) return true;

	return false;
}
