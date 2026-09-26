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


int main() {

    // --------------------------------------------------
    // Input workload
    // --------------------------------------------------

    std::vector<Process> processes;

    processes.emplace_back(1, 0, 8, 3);
    processes.emplace_back(2, 1, 4, 1);
    processes.emplace_back(3, 2, 2, 4);
    processes.emplace_back(4, 3, 6, 2);


    // --------------------------------------------------
    // Create schedulers
    // --------------------------------------------------

    FCFSScheduler fcfs;

    SJFScheduler sjf;

    PriorityScheduler priority;

    RRScheduler roundRobin(2);

    MLFQScheduler mlfq;


    // --------------------------------------------------
    // Run all algorithms
    // --------------------------------------------------

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


    // --------------------------------------------------
    // Display comparison
    // --------------------------------------------------

    ComparisonEngine::displayComparison(
        results
    );


    return 0;
}
