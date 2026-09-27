#ifndef GANTT_CHART_H
#define GANTT_CHART_H

#include <vector>

struct GanttEntry {
    int pid;
    int startTime;
    int endTime;
};

class GanttChart {
private:
    std::vector<GanttEntry> entries;

public:
    void addEntry(int pid, int startTime, int endTime);

    void display() const;

    void clear();

    const std::vector<GanttEntry>& getEntries() const;

    int getBusyTime() const;

    int getSimulationStart() const;

    int getSimulationEnd() const;

    int getElapsedTime() const;

    int getIdleTime() const;

    int getContextSwitchCount() const;
};

#endif
