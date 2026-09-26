#include "GanttChart.h"

#include <iostream>

void GanttChart::addEntry(
    int pid,
    int startTime,
    int endTime
) {
    entries.push_back({
        pid,
        startTime,
        endTime
    });
}

void GanttChart::display() const {

    if (entries.empty()) {
        std::cout << "Gantt Chart is empty.\n";
        return;
    }

    std::cout << "\n===== Gantt Chart =====\n\n";

    // Process names
    for (const auto& entry : entries) {
        std::cout << "| P" << entry.pid << " ";
    }

    std::cout << "|\n";

    // Time values
    std::cout << entries.front().startTime;

    for (const auto& entry : entries) {
        std::cout << "\t" << entry.endTime;
    }

    std::cout << "\n";
}

void GanttChart::clear() {
    entries.clear();
}
