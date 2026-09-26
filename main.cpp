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
#include "CLI.h"


std::vector<SchedulingResult> runAllAlgorithms(
    const std::vector<Process>& processes,
    int timeQuantum) {

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


int main() {

    while (true) {

        CLI::displayMainMenu();

        int choice = CLI::getMenuChoice();


        if (choice == 3) {

            std::cout
                << "\nExiting simulator.\n";

            break;
        }


        std::vector<Process> processes;


        if (choice == 1) {

            processes =
                CLI::inputProcesses();

        } else if (choice == 2) {

            processes =
                CLI::generateSampleWorkload();

            std::cout
                << "\nSample workload loaded.\n";
        }


        std::cout
            << "\nProcesses loaded: "
            << processes.size()
            << "\n";


        int timeQuantum =
            CLI::getTimeQuantum();


        std::vector<SchedulingResult> results =
            runAllAlgorithms(
                processes,
                timeQuantum
            );


        ComparisonEngine::displayComparison(
            results
        );
    }


    return 0;
}
