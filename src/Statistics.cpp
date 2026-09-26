#include "Statistics.h"

#include <numeric>


SchedulingStatistics Statistics::calculate(
    const std::vector<Process>& processes,
    int totalTime,
    int contextSwitches) {

    SchedulingStatistics stats{};

    if (processes.empty() || totalTime <= 0) {
        return stats;
    }

    double totalWaitingTime = 0.0;
    double totalTurnaroundTime = 0.0;
    double totalResponseTime = 0.0;

    int totalBurstTime = 0;

    for (const auto& process : processes) {

        totalWaitingTime +=
            process.getWaitingTime();

        totalTurnaroundTime +=
            process.getTurnaroundTime();

        totalResponseTime +=
            process.getResponseTime();

        totalBurstTime +=
            process.getBurstTime();
    }

    int processCount = processes.size();

    stats.averageWaitingTime =
        totalWaitingTime / processCount;

    stats.averageTurnaroundTime =
        totalTurnaroundTime / processCount;

    stats.averageResponseTime =
        totalResponseTime / processCount;

    stats.cpuUtilization =
        (static_cast<double>(totalBurstTime)
        / totalTime) * 100.0;

    stats.throughput =
        static_cast<double>(processCount)
        / totalTime;

    stats.contextSwitches =
        contextSwitches;

    return stats;
}
