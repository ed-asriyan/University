//
// Created by ed on 31.10.16.
//

#ifndef QUEUE_UNITREQUEST_H
#define QUEUE_UNITREQUEST_H

class RequestUnit {
	private:
		int id;
		int proc_count;

		double income_time = 0;
		double outcome_time = 0;
		double querring_time = 0;

	public:
		RequestUnit(int id, int n_proc);

		int get_id() const;
		int get_n_proc() const;
		double get_income_time() const;
		double get_outcome_time() const;
		double get_querring_time() const;
};

#endif //QUEUE_UNITREQUEST_H
