#ifndef PROCESS_H
#define PROCESS_H

class Process {
private :
	int pid;
	int arrivalTime;
	int burstTime;
	int priority;
	
	int remainingTime;
	int startTime;
	int completionTime;

public :
	//constructor
	Process(int pid, int arrivalTime,int burstTime,int priority);
	
	//getters
	int getPid() const;
	int getArrivalTime() const;
	int getBurstTime() const;
	int getPriority() const;
	int getRemainingTime() const;
	int getStartTime() const;
	int getCompletionTime() const;

	//setters
	void setRemainingTime(int time);
	void setStartTime(int time);
	void setCompletionTime(int time);

	//calculated metrics
	int getTurnaroundTime() const;
	int getWaitingTime() const;
	int getResponseTime() const;

};

#endif
