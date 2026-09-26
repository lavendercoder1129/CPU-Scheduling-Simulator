#ifndef SCHEDULER_H
#define SCHEDULER_H

#include<vector>
#include "Process.h"
using namespace std;
class Scheduler {
public :
	//pure virtual function
	virtual void schedule(vector<Process>& processes) = 0;

	//display scheduling results
	virtual void displayResults(const vector<Process>& process) const = 0;

	virtual ~Scheduler() = default;
};

#endif
