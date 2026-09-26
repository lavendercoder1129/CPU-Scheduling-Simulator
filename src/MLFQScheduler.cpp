#include "MLFQScheduler.h"
#include "SchedulingResult.h"

#include <algorithm>
#include <queue>
#include <vector>


MLFQScheduler::MLFQScheduler() {

    quantum[0] = 2;
    quantum[1] = 4;
    quantum[2] = -1;
}


SchedulingResult MLFQScheduler::schedule(
    const std::vector<Process>& inputProcesses) {

    std::vector<Process> processes = inputProcesses;

    GanttChart ganttChart;

    if (processes.empty()) {

        return SchedulingResult(
            "MLFQ",
            processes,
            ganttChart,
            0,
            0
        );
    }

    const int n = processes.size();

    std::queue<int> queues[QUEUE_COUNT];

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

            queues[0].push(i);
            addedToQueue[i] = true;
        }
    }

    while (completed < n) {

        int selectedQueue = -1;

        for (int q = 0; q < QUEUE_COUNT; q++) {

            if (!queues[q].empty()) {

                selectedQueue = q;
                break;
            }
        }

        if (selectedQueue == -1) {

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

                    queues[0].push(i);
                    addedToQueue[i] = true;
                }
            }

            continue;
        }

        int index =
            queues[selectedQueue].front();

        queues[selectedQueue].pop();

        Process& process =
            processes[index];

        if (process.getStartTime() == -1) {

            process.setStartTime(currentTime);
        }

        int startTime = currentTime;

        int executionTime;

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

                queues[0].push(i);
                addedToQueue[i] = true;
            }
        }

        if (process.getRemainingTime() == 0) {

            process.setCompletionTime(
                currentTime
            );

            completed++;

        } else {

            if (selectedQueue < QUEUE_COUNT - 1) {

                queues[selectedQueue + 1]
                    .push(index);

            } else {

                queues[2].push(index);
            }
        }
    }

    int contextSwitches =
        ganttChart.getEntries().size() > 0
        ? static_cast<int>(ganttChart.getEntries().size()) - 1
        : 0;

    return SchedulingResult(
        "MLFQ",
        processes,
        ganttChart,
        currentTime,
        contextSwitches
    );
}
