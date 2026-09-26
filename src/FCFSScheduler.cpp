#include "FCFSScheduler.h"
#include <algorithm>
#include <iostream>
using namespace std;
void FCFSScheduler :: schedule(vector<Process> &processes){
	//sort according to arrival time of processes
	sort(processes.begin(),processes.end(),[](const Process& a, const Process& b){return a.getArrivalTime() < b.getArrivalTime();});

	int currentTime = 0;
	for(auto &process : processes){
	//cpu  idle if no processarrived
		if(currentTime < process.getArrivalTime()){
			currentTime = process.getArrivalTime();		
		}
		//first process gets cpu
		process.setStartTime(currentTime);
		//execute process
		currentTime +=  process.getBurstTime();
		//process finshes
		process.setCompletionTime(currentTime);
		//process has no rem cpu time
		process.setRemainingTime(0);
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
