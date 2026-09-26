#ifndef STATISTICS_H
#define STATISTICS_H

#include "Process.h"

#include <vector>

struct SchedulingStatistics {

    double averageWaitingTime;
    double averageTurnaroundTime;
    double averageResponseTime;

    double cpuUtilization;
    double throughput;

    int contextSwitches;
};


class Statistics {

public:

    static SchedulingStatistics calculate(
        const std::vector<Process>& processes,
        int totalTime,
        int contextSwitches
    );
};

#endif
