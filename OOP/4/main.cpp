#include <iostream>
#include <iomanip>

#include "Elevator.hpp"

void ShowElevator(const Elevator& elevator) {
	const auto floor_count = elevator.get_floor_count();
	const auto current_floor = elevator.get_current_floor();

	for (int i = static_cast<int>(floor_count) - 1; i >= 0; --i) {
		std::cout << std::setw(4) << i + 1 << ": " << (i == current_floor ? '0' : '.') << std::endl;
	}
}

void OnElevatorMove(const Elevator& elevator) {
	ShowElevator(elevator);
}

int main() {
	Elevator elevator(5);
	elevator.OnMove.connect(&OnElevatorMove);
	ShowElevator(elevator);
	while (true) {
		Elevator::floor_type_t floor;
		std::cin >> floor;
		elevator.JumpToFloor(floor - 1);
	}
	return 0;
}
