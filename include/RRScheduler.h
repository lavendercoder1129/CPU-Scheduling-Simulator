#ifndef RR_SCHEDULER_H
#define RR_SCHEDULER_H

#include "Scheduler.h"

class RRScheduler : public Scheduler {

private:

    int timeQuantum;

public:

    explicit RRScheduler(int quantum);

    SchedulingResult schedule(
        const std::vector<Process>& processes
    ) override;
};

#endif
