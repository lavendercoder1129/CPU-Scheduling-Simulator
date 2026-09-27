#include "Statistics.h"

SchedulingStatistics Statistics::calculate(
    const std::vector<Process>& processes,
    int totalTime,
    int contextSwitches
) {
    SchedulingStatistics stats{};

    if (processes.empty() || totalTime <= 0) {
        return stats;
    }

    double totalWaitingTime = 0.0;
    double totalTurnaroundTime = 0.0;
    double totalResponseTime = 0.0;

    int totalBurstTime = 0;

    for (const auto& process : processes) {
        totalWaitingTime += process.getWaitingTime();
        totalTurnaroundTime += process.getTurnaroundTime();
        totalResponseTime += process.getResponseTime();
        totalBurstTime += process.getBurstTime();
    }

    const double processCount =
        static_cast<double>(processes.size());

    stats.averageWaitingTime =
        totalWaitingTime / processCount;

    stats.averageTurnaroundTime =
        totalTurnaroundTime / processCount;

    stats.averageResponseTime =
        totalResponseTime / processCount;

    stats.cpuUtilization =
        (static_cast<double>(totalBurstTime) /
         static_cast<double>(totalTime)) * 100.0;

    stats.throughput =
        processCount / static_cast<double>(totalTime);

    stats.contextSwitches = contextSwitches;

    return stats;
}

