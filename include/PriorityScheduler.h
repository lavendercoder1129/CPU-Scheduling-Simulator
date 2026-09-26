#ifndef PRIORITY_SCHEDULER_H
#define PRIORITY_SCHEDULER_H

#include "Scheduler.h"

class PriorityScheduler : public Scheduler {

public:

    SchedulingResult schedule(
        const std::vector<Process>& processes
    ) override;
};

#endif
