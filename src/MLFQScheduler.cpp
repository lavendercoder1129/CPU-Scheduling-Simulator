#include "MLFQScheduler.h"

#include <iostream>
#include <vector>
#include <algorithm>


MLFQScheduler::MLFQScheduler() {

    quantum[0] = 2;
    quantum[1] = 4;

    // Queue 2 behaves like FCFS.
    quantum[2] = -1;
}


void MLFQScheduler::schedule(
    std::vector<Process>& processes) {

    if (processes.empty())
        return;

    const int n = processes.size();

    std::queue<int> queues[QUEUE_COUNT];

    std::vector<bool> addedToQueue(n, false);

    int currentTime = 0;
    int completed = 0;

    // Find earliest arrival time
    int earliestArrival =
        processes[0].getArrivalTime();

    for (int i = 1; i < n; i++) {

        earliestArrival =
            std::min(
                earliestArrival,
                processes[i].getArrivalTime()
            );
    }

    currentTime = earliestArrival;

    // Add processes that have already arrived
    for (int i = 0; i < n; i++) {

        if (processes[i].getArrivalTime() <= currentTime) {

            queues[0].push(i);
            addedToQueue[i] = true;
        }
    }


    while (completed < n) {

        int selectedQueue = -1;

        // Find the highest-priority non-empty queue
        for (int q = 0; q < QUEUE_COUNT; q++) {

            if (!queues[q].empty()) {

                selectedQueue = q;
                break;
            }
        }


        // CPU idle
        if (selectedQueue == -1) {

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

            // Add newly arrived processes
            for (int i = 0; i < n; i++) {

                if (!addedToQueue[i] &&
                    processes[i].getArrivalTime() <= currentTime) {

                    queues[0].push(i);
                    addedToQueue[i] = true;
                }
            }

            continue;
        }


        int index = queues[selectedQueue].front();

        queues[selectedQueue].pop();

        Process& process = processes[index];


        // Record first response time
        if (process.getStartTime() == -1) {

            process.setStartTime(currentTime);
        }


        int startTime = currentTime;

        int executionTime;


        // Queue 2 runs until completion
        if (selectedQueue == 2) {

            executionTime =
                process.getRemainingTime();

        } else {

            executionTime =
                std::min(
                    quantum[selectedQueue],
                    process.getRemainingTime()
                );
        }


        currentTime += executionTime;


        process.setRemainingTime(
            process.getRemainingTime()
            - executionTime
        );


        // Record execution in Gantt chart
        ganttChart.addEntry(
            process.getPid(),
            startTime,
            currentTime
        );


        // Add processes that arrived during execution
        for (int i = 0; i < n; i++) {

            if (!addedToQueue[i] &&
                processes[i].getArrivalTime() <= currentTime) {

                queues[0].push(i);
                addedToQueue[i] = true;
            }
        }


        // Process completed
        if (process.getRemainingTime() == 0) {

            process.setCompletionTime(currentTime);

            completed++;

        } else {

            // Move process down one level
            if (selectedQueue < QUEUE_COUNT - 1) {

                queues[selectedQueue + 1].push(index);

            } else {

                // Remain in lowest queue
                queues[2].push(index);
            }
        }
    }
}


void MLFQScheduler::displayResults(
    const std::vector<Process>& processes) const {

    std::cout << "\n";
    std::cout << "===== MLFQ Scheduling =====\n\n";

    std::cout << "Queue Configuration:\n";
    std::cout << "Queue 0 -> Quantum = 2\n";
    std::cout << "Queue 1 -> Quantum = 4\n";
    std::cout << "Queue 2 -> FCFS\n\n";


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


void MLFQScheduler::displayGanttChart() const {

    ganttChart.display();
}
