#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "Process.h"

#include <vector>

class SchedulingResult;

class Scheduler {

public:

    virtual SchedulingResult schedule(
        const std::vector<Process>& processes
    ) = 0;

    virtual ~Scheduler() = default;
};

#endif
