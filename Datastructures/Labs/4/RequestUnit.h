//
// Created by ed on 31.10.16.
//

#ifndef QUEUE_UNITREQUEST_H
#define QUEUE_UNITREQUEST_H

struct RequestUnit {
	int id = 0;
	int proc_count = 0;

	double income_time = 0;
	double outcome_time = 0;
	double querring_time = 0;

	RequestUnit() = default;
	RequestUnit(int id);
};

#endif //QUEUE_UNITREQUEST_H
