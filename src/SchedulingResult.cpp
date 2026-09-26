#include "SchedulingResult.h"


SchedulingResult::SchedulingResult(
    const std::string& algorithmName,
    const std::vector<Process>& processes,
    const GanttChart& ganttChart,
    int totalTime,
    int contextSwitches
)
    : algorithmName(algorithmName),
      processes(processes),
      ganttChart(ganttChart),
      totalTime(totalTime),
      contextSwitches(contextSwitches) {

    statistics =
        Statistics::calculate(
            this->processes,
            totalTime,
            contextSwitches
        );
}


const std::string&
SchedulingResult::getAlgorithmName() const {

    return algorithmName;
}


const std::vector<Process>&
SchedulingResult::getProcesses() const {

    return processes;
}


const GanttChart&
SchedulingResult::getGanttChart() const {

    return ganttChart;
}


const SchedulingStatistics&
SchedulingResult::getStatistics() const {

    return statistics;
}


int SchedulingResult::getTotalTime() const {

    return totalTime;
}


int SchedulingResult::getContextSwitches() const {

    return contextSwitches;
}
