#include "RRScheduler.h"
#include "SchedulingResult.h"

#include <algorithm>
#include <queue>
#include <vector>


RRScheduler::RRScheduler(int quantum)
    : timeQuantum(quantum) {
}


SchedulingResult RRScheduler::schedule(
    const std::vector<Process>& inputProcesses) {

    std::vector<Process> processes = inputProcesses;

    GanttChart ganttChart;

    if (processes.empty()) {

        return SchedulingResult(
            "Round Robin",
            processes,
            ganttChart,
            0,
            0
        );
    }

    int n = processes.size();

    std::queue<int> readyQueue;

    std::vector<bool> addedToQueue(
        n,
        false
    );

    int currentTime = 0;
    int completed = 0;

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

    for (int i = 0; i < n; i++) {

        if (
            processes[i].getArrivalTime()
            <= currentTime
        ) {

            readyQueue.push(i);
            addedToQueue[i] = true;
        }
    }

    while (completed < n) {

        if (readyQueue.empty()) {

            int nextArrival = -1;

            for (int i = 0; i < n; i++) {

                if (addedToQueue[i])
                    continue;

                if (
                    nextArrival == -1 ||
                    processes[i].getArrivalTime()
                    < nextArrival
                ) {

                    nextArrival =
                        processes[i].getArrivalTime();
                }
            }

            currentTime = nextArrival;

            for (int i = 0; i < n; i++) {

                if (
                    !addedToQueue[i] &&
                    processes[i].getArrivalTime()
                    <= currentTime
                ) {

                    readyQueue.push(i);
                    addedToQueue[i] = true;
                }
            }

            continue;
        }

        int index = readyQueue.front();

        readyQueue.pop();

        Process& process =
            processes[index];

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
            process.getRemainingTime()
            - executionTime
        );

        ganttChart.addEntry(
            process.getPid(),
            startTime,
            currentTime
        );

        for (int i = 0; i < n; i++) {

            if (
                !addedToQueue[i] &&
                processes[i].getArrivalTime()
                <= currentTime
            ) {

                readyQueue.push(i);
                addedToQueue[i] = true;
            }
        }

        if (process.getRemainingTime() == 0) {

            process.setCompletionTime(
                currentTime
            );

            completed++;

        } else {

            readyQueue.push(index);
        }
    }

    int contextSwitches =
        ganttChart.getEntries().size() > 0
        ? static_cast<int>(ganttChart.getEntries().size()) - 1
        : 0;

    return SchedulingResult(
        "Round Robin",
        processes,
        ganttChart,
        currentTime,
        contextSwitches
    );
}
