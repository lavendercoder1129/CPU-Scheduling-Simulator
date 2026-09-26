#include <iostream>
#include <vector>

#include "Process.h"
#include "SJFScheduler.h"

int main() {

    std::vector<Process> processes;

    processes.emplace_back(1, 0, 7, 2);
    processes.emplace_back(2, 2, 4, 1);
    processes.emplace_back(3, 3, 2, 3);
    processes.emplace_back(4, 4, 1, 2);

    SJFScheduler sjf;

    sjf.schedule(processes);

    sjf.displayResults(processes);

    sjf.displayGanttChart();

    return 0;
}
