//
// Created by ed on 02.11.16.
//

#include "RandomGenerator.h"

double ::RandomGenerator::GetRandomDouble01() {
	std::random_device rd;
	std::mt19937 e2(rd());
	std::uniform_real_distribution<> dist(0, 1);
	return dist(e2);
}
