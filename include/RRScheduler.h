#ifndef RR_SCHEDULER_H
#define RR_SCHEDULER_H

#include "Scheduler.h"
#include "GanttChart.h"

class RRScheduler : public Scheduler {

private:
    GanttChart ganttChart;
    int timeQuantum;

public:
    explicit RRScheduler(int quantum);

    void schedule(std::vector<Process>& processes) override;

    void displayResults(
        const std::vector<Process>& processes
    ) const override;

    void displayGanttChart() const;
};

#endif
