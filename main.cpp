#include <iostream>
#include <vector>

#include "Process.h"
#include "PriorityScheduler.h"

int main() {

    std::vector<Process> processes;

    processes.emplace_back(1, 0, 7, 3);
    processes.emplace_back(2, 2, 4, 1);
    processes.emplace_back(3, 3, 2, 4);
    processes.emplace_back(4, 4, 1, 2);

    PriorityScheduler scheduler;

    scheduler.schedule(processes);

    scheduler.displayResults(processes);

    scheduler.displayGanttChart();

    return 0;
}
