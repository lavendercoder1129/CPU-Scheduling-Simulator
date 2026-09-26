#include "RRScheduler.h"

#include <iostream>
#include <queue>
#include <vector>

RRScheduler::RRScheduler(int quantum)
    : timeQuantum(quantum) {
}


void RRScheduler::schedule(
    std::vector<Process>& processes) {

    if (processes.empty())
        return;

    int n = processes.size();

    std::queue<int> readyQueue;

    std::vector<bool> addedToQueue(n, false);

    int currentTime = 0;
    int completed = 0;

    // Start from the earliest arrival time
    int earliestArrival = processes[0].getArrivalTime();

    for (int i = 1; i < n; i++) {

        if (processes[i].getArrivalTime() < earliestArrival) {
            earliestArrival =
                processes[i].getArrivalTime();
        }
    }

    currentTime = earliestArrival;

    // Add processes that have already arrived
    for (int i = 0; i < n; i++) {

        if (processes[i].getArrivalTime() <= currentTime) {

            readyQueue.push(i);
            addedToQueue[i] = true;
        }
    }

    while (completed < n) {

        // If queue is empty, CPU is idle
        if (readyQueue.empty()) {

            int nextArrival = -1;

            for (int i = 0; i < n; i++) {

                if (addedToQueue[i])
                    continue;

                if (nextArrival == -1 ||
                    processes[i].getArrivalTime() <
                    nextArrival) {

                    nextArrival =
                        processes[i].getArrivalTime();
                }
            }

            currentTime = nextArrival;

            for (int i = 0; i < n; i++) {

                if (!addedToQueue[i] &&
                    processes[i].getArrivalTime() <= currentTime) {

                    readyQueue.push(i);
                    addedToQueue[i] = true;
                }
            }

            continue;
        }

        int index = readyQueue.front();
        readyQueue.pop();

        Process& process = processes[index];

        // First time process gets CPU
        if (process.getStartTime() == -1) {

            process.setStartTime(currentTime);
        }

        int startTime = currentTime;

        int executionTime =
            std::min(
                timeQuantum,
                process.getRemainingTime()
            );

        currentTime += executionTime;

        process.setRemainingTime(
            process.getRemainingTime() - executionTime
        );

        // Add execution segment to Gantt chart
        ganttChart.addEntry(
            process.getPid(),
            startTime,
            currentTime
        );

        // Add newly arrived processes
        for (int i = 0; i < n; i++) {

            if (!addedToQueue[i] &&
                processes[i].getArrivalTime() <= currentTime) {

                readyQueue.push(i);
                addedToQueue[i] = true;
            }
        }

        // Process finished
        if (process.getRemainingTime() == 0) {

            process.setCompletionTime(currentTime);

            completed++;

        } else {

            // Process did not finish.
            // Put it at the back of the queue.
            readyQueue.push(index);
        }
    }
}


void RRScheduler::displayResults(
    const std::vector<Process>& processes) const {

    std::cout << "\n";
    std::cout << "===== Round Robin Scheduling =====\n\n";

    std::cout << "Time Quantum: "
              << timeQuantum
              << "\n\n";

    std::cout
        << "PID\tAT\tBT\tCT\tTAT\tWT\tRT\n";

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


void RRScheduler::displayGanttChart() const {

    ganttChart.display();
}
