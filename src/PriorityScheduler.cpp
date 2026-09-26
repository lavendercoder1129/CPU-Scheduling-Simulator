#include "PriorityScheduler.h"
#include "SchedulingResult.h"

#include <vector>


SchedulingResult PriorityScheduler::schedule(
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

        for (int i = 0; i < n; i++) {

            if (completedProcess[i])
                continue;

            if (processes[i].getArrivalTime() > currentTime)
                continue;

            if (
                selectedIndex == -1 ||
                processes[i].getPriority()
                < processes[selectedIndex].getPriority()
            ) {

                selectedIndex = i;
            }
        }

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

            currentTime = nextArrival;

            continue;
        }

        Process& process =
            processes[selectedIndex];

        process.setStartTime(currentTime);

        int startTime = currentTime;

        currentTime += process.getBurstTime();

        process.setCompletionTime(currentTime);

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
        ganttChart.getEntries().size() > 0
        ? static_cast<int>(ganttChart.getEntries().size()) - 1
        : 0;

    return SchedulingResult(
        "Priority",
        processes,
        ganttChart,
        currentTime,
        contextSwitches
    );
}
