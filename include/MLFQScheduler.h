#ifndef MLFQ_SCHEDULER_H
#define MLFQ_SCHEDULER_H

#include "Scheduler.h"
#include "GanttChart.h"

#include <queue>

class MLFQScheduler : public Scheduler {

private:
    GanttChart ganttChart;

    static const int QUEUE_COUNT = 3;

    int quantum[QUEUE_COUNT];

public:
    MLFQScheduler();

    void schedule(std::vector<Process>& processes) override;

    void displayResults(
        const std::vector<Process>& processes
    ) const override;

    void displayGanttChart() const;
};

#endif
