//
// Created by ed on 31.10.16.
//

#include "RequestUnit.h"

void RequestUnit::Reset() {
	++proc_count;
	queuing_time = 0;
	service_time = 0;
}
