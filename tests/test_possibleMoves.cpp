#include "doctest/doctest.h"
#include "gameplay/HexPipRules.h"

TEST_CASE("No Scoring Dice") {
	CHECK_FALSE(HasAnyScoringPlay({2, 2, 3, 4, 6, 6}));
}

TEST_CASE("Single Scoring Dice") {
	CHECK(HasAnyScoringPlay({1, 4, 3, 3, 2, 2}));
	CHECK(HasAnyScoringPlay({5, 4, 3, 3, 2, 2}));
	CHECK(HasAnyScoringPlay({5, 1, 3, 3, 2, 2}));
}

TEST_CASE("Triplets") {
	CHECK(HasAnyScoringPlay({1, 1, 1, 4, 3, 3}));
	CHECK(HasAnyScoringPlay({2, 2, 2, 4, 3, 3}));
	CHECK(HasAnyScoringPlay({3, 3, 3, 4, 2, 2}));
	CHECK(HasAnyScoringPlay({4, 4, 4, 2, 3, 3}));
	CHECK(HasAnyScoringPlay({5, 5, 5, 4, 3, 3}));
	CHECK(HasAnyScoringPlay({6, 6, 6, 4, 3, 3}));
}

TEST_CASE("Four of a Kind") {
	CHECK(HasAnyScoringPlay({6, 6, 6, 6, 2, 3}));
}

TEST_CASE("Five of a Kind") {
	CHECK(HasAnyScoringPlay({6, 6, 6, 6, 6, 3}));
}

TEST_CASE("Six of a Kind") {
	CHECK(HasAnyScoringPlay({6, 6, 6, 6, 6, 6}));
}

TEST_CASE("Straight") {
	CHECK(HasAnyScoringPlay({1, 2, 3, 4, 5, 6}));
}

TEST_CASE("Three pairs") {
	CHECK(HasAnyScoringPlay({4, 4, 2, 2, 3, 3}));
}

TEST_CASE("Four of any kind + pair") {
	CHECK(HasAnyScoringPlay({4, 4, 4, 4, 3, 3}));
}

TEST_CASE("Two Triplets") {
	CHECK(HasAnyScoringPlay({3, 3, 3, 2, 2, 2}));
}