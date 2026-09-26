#ifndef FCFS_SCHEDULER_H
#define FCFS_SCHEDULER_H

#include "Scheduler.h"
#include "GanttChart.h"

class FCFSScheduler : public Scheduler {

public:

    SchedulingResult schedule(
        const std::vector<Process>& processes
    ) override;
};

#endif
