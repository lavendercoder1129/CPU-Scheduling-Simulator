#ifndef SJF_SCHEDULER_H
#define SJF_SCHEDULER_H

#include "Scheduler.h"
#include "GanttChart.h"

class SJFScheduler : public Scheduler {
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
