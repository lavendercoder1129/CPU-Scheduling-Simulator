#include <iostream>
#include <vector>

#include "Process.h"
#include "FCFSScheduler.h"

int main() {

    std::vector<Process> processes;

    processes.emplace_back(1, 0, 5, 2);
    processes.emplace_back(2, 1, 3, 1);
    processes.emplace_back(3, 2, 4, 3);

    FCFSScheduler fcfs;

    fcfs.schedule(processes);

    fcfs.displayResults(processes);

    fcfs.displayGanttChart();

    return 0;
}
