#ifndef FCFS_SCHEDULER_H
#define FCFS_SCHEDULER_H

#include "Scheduler.h"
#include "GanttChart.h"

class FCFSScheduler : public Scheduler {
private:
    GanttChart ganttChart;

public:
    void schedule(std::vector<Process>& processes) override;

    void displayResults(
        const std::vector<Process>& processes
    ) const override;

    void displayGanttChart() const;
};

#endif
