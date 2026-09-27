#include <iostream>
#include <vector>

#include "Process.h"
#include "SchedulingResult.h"

#include "FCFSScheduler.h"
#include "SJFScheduler.h"
#include "PriorityScheduler.h"
#include "RRScheduler.h"
#include "MLFQScheduler.h"

#include "ComparisonEngine.h"
#include "StatisticsDisplay.h"
#include "CLI.h"


std::vector<SchedulingResult> runAllAlgorithms(
    const std::vector<Process>& processes,
    int timeQuantum
) {

    FCFSScheduler fcfs;
    SJFScheduler sjf;
    PriorityScheduler priority;
    RRScheduler roundRobin(timeQuantum);
    MLFQScheduler mlfq;

    std::vector<SchedulingResult> results;

    results.push_back(
        fcfs.schedule(processes)
    );

    results.push_back(
        sjf.schedule(processes)
    );

    results.push_back(
        priority.schedule(processes)
    );

    results.push_back(
        roundRobin.schedule(processes)
    );

    results.push_back(
        mlfq.schedule(processes)
    );

    return results;
}


void displayDetailedResults(
    const std::vector<SchedulingResult>& results
) {

    for (const auto& result : results) {

        std::cout
            << "\n\n========================================\n";

        std::cout
            << "        "
            << result.getAlgorithmName()
            << "\n";

        std::cout
            << "========================================\n";

        /*
         * Gantt Chart
         */
        result.getGanttChart().display();

        /*
         * Per-process metrics
         */
        StatisticsDisplay::displayProcessMetrics(
            result.getProcesses()
        );

        /*
         * Scheduling statistics
         */
        StatisticsDisplay::display(
            result.getStatistics()
        );

	const GanttChart& chart =
    		result.getGanttChart();

	std::cout
    		<< "\n===== CPU Time Analysis =====\n\n";

	std::cout
    		<< "CPU Busy Time           : "
    		<< chart.getBusyTime()
    		<< "\n";

	std::cout
    		<< "CPU Idle Time           : "
    		<< chart.getIdleTime()
    		<< "\n";

	std::cout
    		<< "Elapsed Simulation Time : "
    		<< chart.getElapsedTime()
    		<< "\n";

    }
}


int main() {

    while (true) {

        CLI::displayMainMenu();

        int choice =
            CLI::getMenuChoice();

        if (choice == 4) {

            std::cout
                << "\nExiting simulator.\n";

            break;
        }

        std::vector<Process> processes;

        /*
         * Manual workload
         */
        if (choice == 1) {

            processes =
                CLI::inputProcesses();
        }

        /*
         * CSV workload
         */
        else if (choice == 2) {

            processes =
                CLI::loadWorkload();
        }

        /*
         * Sample workload
         */
        else if (choice == 3) {

            processes =
                CLI::generateSampleWorkload();

            std::cout
                << "\nSample workload loaded.\n";
        }

        /*
         * Safety check
         */
        if (processes.empty()) {

            std::cout
                << "\nNo processes loaded.\n";

            continue;
        }

        std::cout
            << "\nProcesses loaded: "
            << processes.size()
            << "\n";

        int timeQuantum =
            CLI::getTimeQuantum();

        /*
         * Run all scheduling algorithms.
         */
        std::vector<SchedulingResult> results =
            runAllAlgorithms(
                processes,
                timeQuantum
            );

        /*
         * Display detailed results
         * for every algorithm.
         */
        displayDetailedResults(results);

        /*
         * Display comparison table.
         */
        ComparisonEngine::displayComparison(
            results
        );
    }

    return 0;
}
