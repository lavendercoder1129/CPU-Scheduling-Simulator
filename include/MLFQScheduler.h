#ifndef MLFQ_SCHEDULER_H
#define MLFQ_SCHEDULER_H

#include "Scheduler.h"

class MLFQScheduler : public Scheduler {

private:

    static const int QUEUE_COUNT = 3;

    int quantum[QUEUE_COUNT];

public:

    MLFQScheduler();

    SchedulingResult schedule(
        const std::vector<Process>& processes
    ) override;
};

#endif
