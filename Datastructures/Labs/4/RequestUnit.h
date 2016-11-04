//
// Created by ed on 31.10.16.
//

#ifndef QUEUE_UNITREQUEST_H
#define QUEUE_UNITREQUEST_H

struct RequestUnit {
	int proc_count = 0;

	double queuing_time = 0;
	double service_time = 0;

	void Reset();
};

#endif //QUEUE_UNITREQUEST_H
