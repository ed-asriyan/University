//
// Created by ed on 08.05.17.
//

#ifndef LAB4_ELEVATOR_HPP
#define LAB4_ELEVATOR_HPP

#include <cstddef>
#include <queue>
#include <stdexcept>

#include <boost/signals2/signal.hpp>

/**
 * Elevator.
 */
class Elevator {
	public:
		typedef size_t floor_type_t;

		/**
		 * Constructor.
		 * @param floor_count Total floor count.
		 * @param current_floor Current floor number.
		 */
		Elevator(floor_type_t floor_count, floor_type_t current_floor = 0);

		/**
		 * Teleports the elevator to the floor_number.
		 * @param floor_number Floor to jump.
		 */
		void JumpToFloor(floor_type_t floor_number);

		/**
		 * Returns total floor count.
		 * @return Total floor count
		 */
		floor_type_t get_floor_count() const;

		/**
		 * Returns floor number which elevator on.
		 * @return Floor number which elevator on.
		 */
		floor_type_t get_current_floor() const;

		/**
		 * Signal which raises when current_floor is changed.
		 */
		boost::signals2::signal<void(const Elevator&)> OnMove;

	private:
		floor_type_t floor_count;
		floor_type_t current_floor;

};

#endif //LAB4_ELEVATOR_HPP
