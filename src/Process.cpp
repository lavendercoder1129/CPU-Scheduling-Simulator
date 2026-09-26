#include "Process.h"

Process::Process(int pid, int arrivalTime, int burstTime, int priority)
	: pid(pid),
	  arrivalTime(arrivalTime),
	  burstTime(burstTime),
	  priority(priority),
	  remainingTime(burstTime),
	  startTime(-1),
     	  completionTime(-1){
}

//getters

int Process::getPid() const{
	return pid;
}
int Process::getArrivalTime() const{
	return arrivalTime;
}

int Process::getBurstTime() const {
	return burstTime;
} 

int Process::getPriority () const {
	return priority;
}

int Process::getRemainingTime() const {
	return remainingTime;
}

int Process::getStartTime() const {
    return startTime;
}

int Process::getCompletionTime() const {
    return completionTime;
}

//setter functions

void Process::setRemainingTime(int time) {
    remainingTime = time;
}

void Process::setStartTime(int time) {
    startTime = time;
}

void Process::setCompletionTime(int time) {
    completionTime = time;
}

//metrics

int Process::getTurnaroundTime() const{
	return completionTime - arrivalTime;
}
int  Process::getWaitingTime() const {
	return getTurnaroundTime() -  burstTime;
}
int Process::getResponseTime() const{
	return startTime - arrivalTime;
}

