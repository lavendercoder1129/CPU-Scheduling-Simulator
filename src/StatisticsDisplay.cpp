#include "StatisticsDisplay.h"

#include <iomanip>
#include <iostream>
#include <string>

void StatisticsDisplay::display(
    const SchedulingStatistics& stats
) {

    std::cout
        << "\n===== Scheduling Statistics =====\n\n";

    std::cout
        << std::fixed
        << std::setprecision(2);

    std::cout
        << "Average Waiting Time    : "
        << stats.averageWaitingTime
        << "\n";

    std::cout
        << "Average Turnaround Time : "
        << stats.averageTurnaroundTime
        << "\n";

    std::cout
        << "Average Response Time   : "
        << stats.averageResponseTime
        << "\n";

    std::cout
        << "CPU Utilization         : "
        << stats.cpuUtilization
        << "%\n";

    std::cout
        << "Throughput              : "
        << stats.throughput
        << " processes/unit time\n";

    std::cout
        << "Context Switches        : "
        << stats.contextSwitches
        << "\n";
}


void StatisticsDisplay::displayProcessMetrics(
    const std::vector<Process>& processes
) {

    if (processes.empty()) {

        std::cout
            << "\nNo process data available.\n";

        return;
    }

    std::cout
        << "\n===== Process Metrics =====\n\n";

    std::cout
        << std::left
        << std::setw(8) << "PID"
        << std::setw(8) << "AT"
        << std::setw(8) << "BT"
        << std::setw(10) << "Priority"
        << std::setw(8) << "CT"
        << std::setw(8) << "TAT"
        << std::setw(8) << "WT"
        << std::setw(8) << "RT"
        << "\n";

    std::cout
        << std::string(66, '-')
        << "\n";

    for (const auto& process : processes) {

        std::cout
            << std::left

            << std::setw(8)
            << process.getPid()

            << std::setw(8)
            << process.getArrivalTime()

            << std::setw(8)
            << process.getBurstTime()

            << std::setw(10)
            << process.getPriority()

            << std::setw(8)
            << process.getCompletionTime()

            << std::setw(8)
            << process.getTurnaroundTime()

            << std::setw(8)
            << process.getWaitingTime()

            << std::setw(8)
            << process.getResponseTime()

            << "\n";
    }
}
