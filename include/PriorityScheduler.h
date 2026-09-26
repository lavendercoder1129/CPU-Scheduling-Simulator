#ifndef PRIORITY_SCHEDULER_H
#define PRIORITY_SCHEDULER_H

#include "Scheduler.h"
#include "GanttChart.h"

class PriorityScheduler : public Scheduler {

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
