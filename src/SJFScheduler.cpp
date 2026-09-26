#include "SJFScheduler.h"

#include <algorithm>
#include <iostream>
#include <vector>

void SJFScheduler::schedule(
    std::vector<Process>& processes
) {

    int currentTime = 0;
    int completed = 0;
    int n = processes.size();

    // Keep track of which processes are completed
    std::vector<bool> completedProcess(n, false);

    while (completed < n) {

        int selectedIndex = -1;

        // Find the shortest available process
        for (int i = 0; i < n; i++) {

            if (completedProcess[i]) {
                continue;
            }

            if (processes[i].getArrivalTime() > currentTime) {
                continue;
            }

            if (selectedIndex == -1 ||
                processes[i].getBurstTime() <
                processes[selectedIndex].getBurstTime()) {

                selectedIndex = i;
            }
        }

        // No process is currently available
        if (selectedIndex == -1) {

            int nextArrival = -1;

            for (int i = 0; i < n; i++) {

                if (completedProcess[i]) {
                    continue;
                }

                if (nextArrival == -1 ||
                    processes[i].getArrivalTime() < nextArrival) {

                    nextArrival =
                        processes[i].getArrivalTime();
                }
            }

            currentTime = nextArrival;
            continue;
        }

        Process& process = processes[selectedIndex];

        // Process starts execution
        process.setStartTime(currentTime);

        int startTime = currentTime;

        // Execute process
        currentTime += process.getBurstTime();

        // Process completes
        process.setCompletionTime(currentTime);
        process.setRemainingTime(0);

        // Add execution interval to Gantt chart
        ganttChart.addEntry(
            process.getPid(),
            startTime,
            currentTime
        );

        completedProcess[selectedIndex] = true;
        completed++;
    }
}

void SJFScheduler::displayResults(
    const std::vector<Process>& processes
) const {

    std::cout << "\n";
    std::cout << "===== SJF Scheduling =====\n\n";

    std::cout << "PID\tAT\tBT\tCT\tTAT\tWT\tRT\n";

    std::cout
        << "------------------------------------------------\n";

    for (const auto& process : processes) {

        std::cout
            << "P" << process.getPid() << "\t"
            << process.getArrivalTime() << "\t"
            << process.getBurstTime() << "\t"
            << process.getCompletionTime() << "\t"
            << process.getTurnaroundTime() << "\t"
            << process.getWaitingTime() << "\t"
            << process.getResponseTime()
            << "\n";
    }
}

void SJFScheduler::displayGanttChart() const {
    ganttChart.display();
}
