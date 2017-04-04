//
// Created by ed on 31.03.17.
//

#include "Utils.hpp"


Utils::PointsTable Utils::GenerateTable(
	const std::function<double(double)>& func,
	double x_begin,
	double x_end,
	double x_step
) {
	int count = static_cast<int>((x_end - x_begin) / x_step) + 1;
	Utils::PointsTable result(static_cast<unsigned int>(count));
	for (int i = 0; i < count; ++i) {
		double x = x_begin + i * x_step;
		result[i].x = x;
		result[i].y = func(x);
	}
	return result;
}
