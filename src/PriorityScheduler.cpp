#include "PriorityScheduler.h"

#include <iostream>
#include <vector>

void PriorityScheduler::schedule(
    std::vector<Process>& processes) {

    int currentTime = 0;
    int completed = 0;
    int n = processes.size();

    std::vector<bool> completedProcess(n, false);

    while (completed < n) {

        int selectedIndex = -1;

        // Find highest-priority process among arrived processes
        for (int i = 0; i < n; i++) {

            if (completedProcess[i])
                continue;

            if (processes[i].getArrivalTime() > currentTime)
                continue;

            // Lower priority number = higher priority
            if (selectedIndex == -1 ||
                processes[i].getPriority() <
                processes[selectedIndex].getPriority()) {

                selectedIndex = i;
            }
        }

        // No process has arrived yet
        if (selectedIndex == -1) {

            int nextArrival = -1;

            for (int i = 0; i < n; i++) {

                if (completedProcess[i])
                    continue;

                if (nextArrival == -1 ||
                    processes[i].getArrivalTime() < nextArrival) {

                    nextArrival =
                        processes[i].getArrivalTime();
                }
            }

            currentTime = nextArrival;
            continue;
        }

        // Execute selected process
        Process& process = processes[selectedIndex];

        process.setStartTime(currentTime);

        int startTime = currentTime;

        currentTime += process.getBurstTime();

        process.setCompletionTime(currentTime);

        process.setRemainingTime(0);

        // Add execution to Gantt chart
        ganttChart.addEntry(
            process.getPid(),
            startTime,
            currentTime
        );

        completedProcess[selectedIndex] = true;
        completed++;
    }
}


void PriorityScheduler::displayResults(
    const std::vector<Process>& processes) const {

    std::cout << "\n";
    std::cout << "===== Priority Scheduling =====\n\n";

    std::cout << "PID\tAT\tBT\tP\tCT\tTAT\tWT\tRT\n";

    std::cout
        << "--------------------------------------------------------\n";

    for (const auto& process : processes) {

        std::cout
            << "P" << process.getPid() << "\t"
            << process.getArrivalTime() << "\t"
            << process.getBurstTime() << "\t"
            << process.getPriority() << "\t"
            << process.getCompletionTime() << "\t"
            << process.getTurnaroundTime() << "\t"
            << process.getWaitingTime() << "\t"
            << process.getResponseTime()
            << "\n";
    }
}


void PriorityScheduler::displayGanttChart() const {

    ganttChart.display();
}
