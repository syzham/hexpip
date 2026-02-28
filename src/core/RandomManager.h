#ifndef HEXPIP_RANDOMMANAGER_H
#define HEXPIP_RANDOMMANAGER_H

#include <random>

class RandomManager {
public:
	void init(unsigned seed);
	int getRandomNumber(int min, int max);

private:
	std::mt19937 m_generator;
};


#endif //HEXPIP_RANDOMMANAGER_H