#include "FCFSScheduler.h"
#include <algorithm>
#include <iostream>
using namespace std;
void FCFSScheduler :: schedule(vector<Process> &processes){
	//sort according to arrival time of processes
	sort(processes.begin(),processes.end(),[](const Process& a, const Process& b){return a.getArrivalTime() < b.getArrivalTime();});

	int currentTime = 0;
	for (auto& process : processes) {

	 	if (currentTime < process.getArrivalTime()) {
        		currentTime = process.getArrivalTime();
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
}

void FCFSScheduler::displayResults(
    const std::vector<Process>& processes
) const {

    std::cout << "\n";
    std::cout << "===== FCFS Scheduling =====\n\n";

    std::cout
        << "PID\tAT\tBT\tCT\tTAT\tWT\tRT\n";

    std::cout
        << "----------------------------------------"
        << "----------------\n";

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
void FCFSScheduler::displayGanttChart() const {
    ganttChart.display();
}

