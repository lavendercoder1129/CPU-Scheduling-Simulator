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

    /*
     * Add initial CPU idle time if the first process
     * arrives after time 0.
     */
    int earliestArrival =
        processes[0].getArrivalTime();

    for (int i = 1; i < n; i++) {

        earliestArrival =
            std::min(
                earliestArrival,
                processes[i].getArrivalTime()
            );
    }

    if (currentTime < earliestArrival) {

        ganttChart.addEntry(
            -1,
            currentTime,
            earliestArrival
        );

        currentTime = earliestArrival;
    }

    /*
     * Add all processes that have arrived
     * to the highest-priority queue.
     */
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

        /*
         * Always select the highest-priority
         * non-empty queue.
         */
        for (
            int q = 0;
            q < QUEUE_COUNT;
            q++
        ) {

            if (!queues[q].empty()) {

                selectedQueue = q;
                break;
            }
        }

        /*
         * No process is currently ready.
         * Advance to the next process arrival
         * and record CPU idle time.
         */
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

            if (
                nextArrival != -1 &&
                currentTime < nextArrival
            ) {

                ganttChart.addEntry(
                    -1,
                    currentTime,
                    nextArrival
                );

                currentTime = nextArrival;
            }

            /*
             * Add all processes that have now arrived
             * to Queue 0.
             */
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

        /*
         * Response time is based on the first
         * time the process gets CPU.
         */
        if (process.getStartTime() == -1) {

            process.setStartTime(currentTime);
        }

        int startTime = currentTime;

        int executionTime;

        /*
         * Queue 2 is the lowest-priority queue
         * and runs processes until completion.
         */
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

        /*
         * Record this CPU execution segment.
         */
        ganttChart.addEntry(
            process.getPid(),
            startTime,
            currentTime
        );

        /*
         * Add newly arrived processes to Queue 0.
         */
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

        /*
         * Process has finished.
         */
        if (process.getRemainingTime() == 0) {

            process.setCompletionTime(
                currentTime
            );

            completed++;

        } else {

            /*
             * Process did not finish.
             * Demote it to the next queue.
             */
            if (
                selectedQueue
                < QUEUE_COUNT - 1
            ) {

                queues[selectedQueue + 1]
                    .push(index);

            } else {

                /*
                 * Already in the lowest queue.
                 * Keep it there.
                 */
                queues[2].push(index);
            }
        }
    }

    int contextSwitches =
        ganttChart.getContextSwitchCount();

    return SchedulingResult(
        "MLFQ",
        processes,
        ganttChart,
        currentTime,
        contextSwitches
    );
}
