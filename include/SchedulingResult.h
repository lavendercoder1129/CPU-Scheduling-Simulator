#ifndef SCHEDULING_RESULT_H
#define SCHEDULING_RESULT_H

#include "Process.h"
#include "GanttChart.h"
#include "Statistics.h"

#include <string>
#include <vector>

class SchedulingResult {

private:

    std::string algorithmName;

    std::vector<Process> processes;

    GanttChart ganttChart;

    SchedulingStatistics statistics;

    int totalTime;
    int contextSwitches;

public:

    SchedulingResult(
        const std::string& algorithmName,
        const std::vector<Process>& processes,
        const GanttChart& ganttChart,
        int totalTime,
        int contextSwitches
    );

    const std::string& getAlgorithmName() const;

    const std::vector<Process>& getProcesses() const;

    const GanttChart& getGanttChart() const;

    const SchedulingStatistics& getStatistics() const;

    int getTotalTime() const;

    int getContextSwitches() const;
};

#endif
