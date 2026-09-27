#include "SJFScheduler.h"
#include "SchedulingResult.h"

#include <vector>


SchedulingResult SJFScheduler::schedule(
    const std::vector<Process>& inputProcesses) {

    std::vector<Process> processes = inputProcesses;

    GanttChart ganttChart;

    int currentTime = 0;
    int completed = 0;

    int n = processes.size();

    std::vector<bool> completedProcess(
        n,
        false
    );

    while (completed < n) {

        int selectedIndex = -1;

        /*
         * Select the shortest available process.
         *
         * Tie-breaking:
         * 1. Burst time
         * 2. Arrival time
         * 3. PID
         */
        for (int i = 0; i < n; i++) {

            if (completedProcess[i])
                continue;

            if (
                processes[i].getArrivalTime()
                > currentTime
            ) {
                continue;
            }

            if (
                selectedIndex == -1 ||
                processes[i].getBurstTime()
                    < processes[selectedIndex].getBurstTime() ||
                (
                    processes[i].getBurstTime()
                        == processes[selectedIndex].getBurstTime() &&
                    processes[i].getArrivalTime()
                        < processes[selectedIndex].getArrivalTime()
                ) ||
                (
                    processes[i].getBurstTime()
                        == processes[selectedIndex].getBurstTime() &&
                    processes[i].getArrivalTime()
                        == processes[selectedIndex].getArrivalTime() &&
                    processes[i].getPid()
                        < processes[selectedIndex].getPid()
                )
            ) {

                selectedIndex = i;
            }
        }

        /*
         * No process is currently available.
         * Advance to the next arrival and record
         * CPU idle time.
         */
        if (selectedIndex == -1) {

            int nextArrival = -1;

            for (int i = 0; i < n; i++) {

                if (completedProcess[i])
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

            continue;
        }

        Process& process =
            processes[selectedIndex];

        /*
         * First time the process gets CPU.
         */
        process.setStartTime(currentTime);

        int startTime = currentTime;

        /*
         * Non-preemptive SJF:
         * run the selected process until completion.
         */
        currentTime +=
            process.getBurstTime();

        process.setCompletionTime(
            currentTime
        );

        process.setRemainingTime(0);

        ganttChart.addEntry(
            process.getPid(),
            startTime,
            currentTime
        );

        completedProcess[selectedIndex] = true;

        completed++;
    }

    int contextSwitches =
        ganttChart.getContextSwitchCount();

    return SchedulingResult(
        "SJF",
        processes,
        ganttChart,
        currentTime,
        contextSwitches
    );
}