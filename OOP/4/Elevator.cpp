//
// Created by ed on 08.05.17.
//

#include "Elevator.hpp"

Elevator::Elevator(floor_type_t floor_count, floor_type_t current_floor)
	: floor_count(floor_count), current_floor(current_floor) {
	if (current_floor >= floor_count) throw std::invalid_argument("current_floor must be less then floor_count");
}

void Elevator::JumpToFloor(Elevator::floor_type_t floor_number) {
	if (floor_number >= floor_count) throw std::invalid_argument("floor_number must be less then floor count");
	current_floor = floor_number;
}

Elevator::floor_type_t Elevator::get_floor_count() const {
	return floor_count;
}

Elevator::floor_type_t Elevator::get_current_floor() const {
	return current_floor;
}
