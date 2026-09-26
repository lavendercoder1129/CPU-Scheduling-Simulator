#ifndef FCFS_SCHEDULER_H
#define FCFS_SCHEDULER_H

#include "Scheduler.h"

class FCFSScheduler : public Scheduler {
public:
    void schedule(std::vector<Process>& processes) override;

    void displayResults(
        const std::vector<Process>& processes
    ) const override;
};

#endif
