#include "FCFSScheduler.h"
#include "SchedulingResult.h"

#include <algorithm>
#include <vector>


SchedulingResult FCFSScheduler::schedule(
    const std::vector<Process>& inputProcesses) {

    std::vector<Process> processes = inputProcesses;

    GanttChart ganttChart;

    std::sort(
        processes.begin(),
        processes.end(),
        [](const Process& a, const Process& b) {

            if (a.getArrivalTime() != b.getArrivalTime()) {
                return a.getArrivalTime() < b.getArrivalTime();
            }

            return a.getPid() < b.getPid();
        }
    );

    int currentTime = 0;

    for (auto& process : processes) {

        if (currentTime < process.getArrivalTime()) {
            ganttChart.addEntry(-1,currentTime,process.getArrivalTime());
	    currentTime =   process.getArrivalTime();        
	}
	

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
    }

    int contextSwitches = ganttChart.getContextSwitchCount();

    return SchedulingResult(
        "FCFS",
        processes,
        ganttChart,
        currentTime,
        contextSwitches
    );
}
