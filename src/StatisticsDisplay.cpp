#include "StatisticsDisplay.h"

#include <iomanip>
#include <iostream>


void StatisticsDisplay::display(
    const SchedulingStatistics& stats) {

    std::cout << "\n";
    std::cout << "===== Scheduling Statistics =====\n\n";

    std::cout << std::fixed
              << std::setprecision(2);

    std::cout
        << "Average Waiting Time   : "
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
        << "CPU Utilization        : "
        << stats.cpuUtilization
        << "%\n";

    std::cout
        << "Throughput             : "
        << stats.throughput
        << " processes/unit time\n";

    std::cout
        << "Context Switches       : "
        << stats.contextSwitches
        << "\n";
}
