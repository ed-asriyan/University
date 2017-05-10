//
// Created by ed on 08.05.17.
//

#include "Elevator.hpp"

#define assert_floor(floor) assert((floor) < floor_count);

Elevator::Elevator(floor_type_t floor_count, floor_type_t current_floor)
	: floor_count(floor_count), current_floor(current_floor) {
	throwIfOverflow(current_floor);
}

void Elevator::jumpToFloor(Elevator::floor_type_t floor_number) {
	assert_floor(floor_number);
	current_floor = floor_number;
	OnMove(*this);
}

Elevator::floor_type_t Elevator::get_floor_count() const {
	return floor_count;
}

Elevator::floor_type_t Elevator::get_current_floor() const {
	return current_floor;
}

void Elevator::MoveToFloor(Elevator::floor_type_t floor_number) {
	throwIfOverflow(floor_number);
	if (floor_number == current_floor) {
		return;
	}

	if (floor_number > current_floor) {
		for (auto i = current_floor + 1; i < floor_number; ++i) {
			jumpToFloor(i);
		}
	} else {
		for (auto i = current_floor - 1; i > floor_number; --i) {
			jumpToFloor(i);
		}
	}
	jumpToFloor(floor_number);
}

void Elevator::throwIfOverflow(Elevator::floor_type_t floor_number) const {
	if (floor_number >= floor_count) throw std::invalid_argument("Floor number is out of range");
}
