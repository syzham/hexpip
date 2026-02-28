#include "RandomManager.h"

void RandomManager::init(const unsigned seed) {
	m_generator = std::mt19937(seed);
}

int RandomManager::getRandomNumber(int min, int max) {
	std::uniform_int_distribution<int> distribution(1, 6);
	return distribution(m_generator);
}
