//
// Created by ed on 09.04.17.
//

#include <iostream>

#include "Point2d.h"

int main(int argc, const char* argv[]) {
	double x_begin;
	std::cout << "Enter left  x border: ";
	std::cin >> x_begin;

	double x_end;
	std::cout << "Enter right x border: ";
	std::cin >> x_end;

	double y_begin;
	std::cout << "Enter left  y border: ";
	std::cin >> y_begin;

	double y_end;
	std::cout << "Enter right y border: ";
	std::cin >> y_end;

	Point2d point;
	std::cout << "Enter x:";
	std::cin >> point.x;
	std::cout << "Enter y:";
	std::cin >> point.y;

	unsigned int x_degree;
	std::cout << "Enter x degree: ";
	std::cin >> x_degree;

	unsigned int y_degree;
	std::cout << "Enter y degree: ";
	std::cin >> y_degree;

	return 0;
}
