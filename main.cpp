#include <iostream>
#include <vector>

#include "Process.h"
#include "MLFQScheduler.h"

int main() {

    std::vector<Process> processes;

    processes.emplace_back(1, 0, 8, 1);
    processes.emplace_back(2, 1, 4, 2);
    processes.emplace_back(3, 2, 2, 3);
    processes.emplace_back(4, 3, 6, 4);

    MLFQScheduler scheduler;

    scheduler.schedule(processes);

    scheduler.displayResults(processes);

    scheduler.displayGanttChart();

    return 0;
}
