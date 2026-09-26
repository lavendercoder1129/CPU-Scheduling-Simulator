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
};

#endif
