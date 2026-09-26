#include <iostream>
#include <vector>

#include "Process.h"
#include "RRScheduler.h"

int main() {

    std::vector<Process> processes;

    processes.emplace_back(1, 0, 5, 1);
    processes.emplace_back(2, 1, 4, 2);
    processes.emplace_back(3, 2, 2, 3);
    processes.emplace_back(4, 3, 1, 4);

    int timeQuantum = 2;

    RRScheduler scheduler(timeQuantum);

    scheduler.schedule(processes);

    scheduler.displayResults(processes);

    scheduler.displayGanttChart();

    return 0;
}
