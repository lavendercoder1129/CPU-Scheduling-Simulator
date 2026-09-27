#include "GanttChart.h"
#include <iostream>

void GanttChart::addEntry(int pid, int startTime, int endTime) {
    if (endTime <= startTime) {
        return;
    }

    entries.push_back({pid, startTime, endTime});
}

void GanttChart::display() const {
    if (entries.empty()) {
        std::cout << "Gantt Chart is empty.\n";
        return;
    }

    std::cout << "\n===== Gantt Chart =====\n\n";

    for (const auto& entry : entries) {
        if (entry.pid == -1) {
            std::cout << "| IDLE ";
        } else {
            std::cout << "| P" << entry.pid << " ";
        }
    }

    std::cout << "|\n";

    std::cout << entries.front().startTime;

    for (const auto& entry : entries) {
        std::cout << "\t" << entry.endTime;
    }

    std::cout << "\n";
}

void GanttChart::clear() {
    entries.clear();
}

const std::vector<GanttEntry>& GanttChart::getEntries() const {
    return entries;
}

int GanttChart::getBusyTime() const {
    int busyTime = 0;

    for (const auto& entry : entries) {
        if (entry.pid != -1) {
            busyTime += entry.endTime - entry.startTime;
        }
    }

    return busyTime;
}

int GanttChart::getSimulationStart() const {
    if (entries.empty()) {
        return 0;
    }

    return entries.front().startTime;
}

int GanttChart::getSimulationEnd() const {
    if (entries.empty()) {
        return 0;
    }

    return entries.back().endTime;
}

int GanttChart::getElapsedTime() const {
    return getSimulationEnd() - getSimulationStart();
}

int GanttChart::getIdleTime() const {
    return getElapsedTime() - getBusyTime();
}

int GanttChart::getContextSwitchCount() const {
    if (entries.size() <= 1) {
        return 0;
    }

    int contextSwitches = 0;

    for (size_t i = 1; i < entries.size(); ++i) {
        const auto& previous = entries[i - 1];
        const auto& current = entries[i];

        // Count a switch only when the executing process changes.
        // Idle periods are not considered a context switch.
        if (previous.pid != -1 &&
            current.pid != -1 &&
            previous.pid != current.pid) {
            ++contextSwitches;
        }
    }

    return contextSwitches;
}
