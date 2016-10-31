//
// Created by ed on 31.10.16.
//

#include "RequestUnit.h"

int RequestUnit::get_id() const {
	return id;
}

int RequestUnit::get_n_proc() const {
	return proc_count;
}

double RequestUnit::get_income_time() const {
	return income_time;
}

double RequestUnit::get_outcome_time() const {
	return outcome_time;
}

double RequestUnit::get_querring_time() const {
	return querring_time;
}

RequestUnit::RequestUnit(int id) : id(id) {}
