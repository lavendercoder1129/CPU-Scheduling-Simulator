#ifndef SJF_SCHEDULER_H
#define SJF_SCHEDULER_H

#include "Scheduler.h"

class SJFScheduler : public Scheduler {

public:

    SchedulingResult schedule(
        const std::vector<Process>& processes
    ) override;
};

#endif
