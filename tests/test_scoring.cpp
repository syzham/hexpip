#include "doctest/doctest.h"
#include "gameplay/HexPipRules.h"

TEST_CASE("Non-scoring dice makes selection invalid") {
	SUBCASE("Non-scoring dice") {
		auto [points, validSelection] = ScoreDiceFaces({2, 2, 3, 4, 6, 6});
		CHECK_FALSE(validSelection);
		CHECK(points == 0);
	}

	SUBCASE("singles + non scoring dice") {
		auto [points, validSelection] = ScoreDiceFaces({1, 2, 3, 5, 6, 6});
		CHECK_FALSE(validSelection);
		CHECK(points == 0);
	}

	SUBCASE("triples with + non scoring dice") {
		auto [points, validSelection] = ScoreDiceFaces({1, 1, 1, 5, 6, 6});
		CHECK_FALSE(validSelection);
		CHECK(points == 0);
	}

	SUBCASE("four of a kind with + non scoring dice") {
		auto [points, validSelection] = ScoreDiceFaces({1, 1, 1, 1, 4, 6});
		CHECK_FALSE(validSelection);
		CHECK(points == 0);
	}

	SUBCASE("five of a kind with + non scoring dice") {
		auto [points, validSelection] = ScoreDiceFaces({1, 1, 1, 1, 1, 6});
		CHECK_FALSE(validSelection);
		CHECK(points == 0);
	}
}

TEST_CASE("Singles score correctly") {
	SUBCASE("1 Dice") {
		auto [points, validSelection] = ScoreDiceFaces({1});
		CHECK(validSelection);
		CHECK(points == 100);
	}

	SUBCASE("5 Dice") {
		auto [points, validSelection] = ScoreDiceFaces({5});
		CHECK(validSelection);
		CHECK(points == 50);
	}

	SUBCASE("5 and 1 combo") {
		auto [points, validSelection] = ScoreDiceFaces({5, 1, 1, 5});
		CHECK(validSelection);
		CHECK(points == 300);
	}
}

TEST_CASE("Three of a kind") {
	SUBCASE ("1 three of a kind") {
		auto [points, validSelection] = ScoreDiceFaces({1,1,1});
		CHECK(validSelection);
		CHECK(points == 1000);
	}

	SUBCASE ("2 Three of a kind") {
		auto [points, validSelection] = ScoreDiceFaces({2,2,2});
		CHECK(validSelection);
		CHECK(points == 200);
	}

	SUBCASE ("3 Three of kind") {
		auto [points, validSelection] = ScoreDiceFaces({3,3,3});
		CHECK(validSelection);
		CHECK(points == 300);
	}

	SUBCASE ("4 Three of a kind") {
		auto [points, validSelection] = ScoreDiceFaces({4,4,4});
		CHECK(validSelection);
		CHECK(points == 400);
	}

	SUBCASE ("5 Three of a kind") {
		auto [points, validSelection] = ScoreDiceFaces({5,5,5});
		CHECK(validSelection);
		CHECK(points == 500);
	}

	SUBCASE ("6 Three of a kind") {
		auto [points, validSelection] = ScoreDiceFaces({6,6,6});
		CHECK(validSelection);
		CHECK(points == 600);
	}
}

TEST_CASE("Four/five/six of a kind") {

	SUBCASE ("four of a kind") {
		auto [points, validSelection] = ScoreDiceFaces({1,1,1,1});
		CHECK(validSelection);
		CHECK(points == 1000);
	}

	SUBCASE ("five of a kind") {
		auto [points, validSelection] = ScoreDiceFaces({1,1,1,1,1});
		CHECK(validSelection);
		CHECK(points == 2000);
	}

	SUBCASE ("six of a kind") {
		auto [points, validSelection] = ScoreDiceFaces({1,1,1,1,1,1});
		CHECK(validSelection);
		CHECK(points == 3000);
	}
}

TEST_CASE("Straight 1-6") {
	auto [points, validSelection] = ScoreDiceFaces({1,2,3,4,5,6});
	CHECK(validSelection);
	CHECK(points == 1500);
}

TEST_CASE("Three pairs") {
	auto [points, validSelection] = ScoreDiceFaces({1,1,2,2,3,3});
	CHECK(validSelection);
	CHECK(points == 1500);
}

TEST_CASE("Four of a kind + a pair") {
	auto [points, validSelection] = ScoreDiceFaces({1,1,1,1,2,2});
	CHECK(validSelection);
	CHECK(points == 1500);
}

TEST_CASE("Two Triplets") {
	auto [points, validSelection] = ScoreDiceFaces({1,1,1,2,2,2});
	CHECK(validSelection);
	CHECK(points == 2500);
}

TEST_CASE("Combo scoring") {
	SUBCASE("Five of a king + 1") {
		auto [points, validSelection] = ScoreDiceFaces({4,4,4,4,4,1});
		CHECK(validSelection);
		CHECK(points == 2100);
	}

	SUBCASE ("Four of a kind + 1 + 5") {
		auto [points, validSelection] = ScoreDiceFaces({4,4,4,4,5,1});
		CHECK(validSelection);
		CHECK(points == 1150);
	}

	SUBCASE ("Three of a kind + 1 + 1 + 5") {
		auto [points, validSelection] = ScoreDiceFaces({4,4,4,1,1,5});
		CHECK(validSelection);
		CHECK(points == 650);
	}
}
