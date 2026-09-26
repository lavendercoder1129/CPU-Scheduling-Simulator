#include "ComparisonEngine.h"

#include <iomanip>
#include <iostream>


void ComparisonEngine::displayComparison(
    const std::vector<SchedulingResult>& results) {

    if (results.empty()) {

        std::cout
            << "\nNo scheduling results available.\n";

        return;
    }

    std::cout << "\n\n";

    std::cout
        << "==========================================================================\n";

    std::cout
        << "                       ALGORITHM COMPARISON\n";

    std::cout
        << "==========================================================================\n\n";


    std::cout << std::left
              << std::setw(18) << "Algorithm"
              << std::setw(12) << "Avg WT"
              << std::setw(12) << "Avg TAT"
              << std::setw(12) << "Avg RT"
              << std::setw(14) << "CPU Util."
              << std::setw(14) << "Throughput"
              << std::setw(12) << "Context"
              << "\n";


    std::cout
        << "--------------------------------------------------------------------------\n";


    std::cout << std::fixed
              << std::setprecision(2);


    for (const auto& result : results) {

        const auto& stats =
            result.getStatistics();

        std::cout
            << std::left
            << std::setw(18)
            << result.getAlgorithmName()

            << std::setw(12)
            << stats.averageWaitingTime

            << std::setw(12)
            << stats.averageTurnaroundTime

            << std::setw(12)
            << stats.averageResponseTime

            << std::setw(14)
            << stats.cpuUtilization

            << std::setw(14)
            << stats.throughput

            << std::setw(12)
            << stats.contextSwitches

            << "\n";
    }


    std::cout
        << "==========================================================================\n";
}
