#include "GanttChart.h"

#include <iomanip>
#include <iostream>

void GanttChart::addEntry(
    int pid,
    int startTime,
    int endTime
) {
    if (endTime <= startTime) {
        return;
    }

    entries.push_back({
        pid,
        startTime,
        endTime
    });
}

void GanttChart::display() const {

    if (entries.empty()) {
        std::cout << "\nGantt Chart is empty.\n";
        return;
    }

    std::cout << "\n===== Gantt Chart =====\n\n";

    /*
     * Process labels
     */
    for (const auto& entry : entries) {

        std::string label;

        if (entry.pid == -1) {
            label = "IDLE";
        } else {
            label = "P" + std::to_string(entry.pid);
        }

        std::cout << "| "
                  << std::setw(6)
                  << std::left
                  << label
                  << " ";
    }

    std::cout << "|\n";

    /*
     * Timeline
     */
    for (const auto& entry : entries) {

        std::cout << std::setw(9)
                  << std::left
                  << entry.startTime;
    }

    if (!entries.empty()) {

        std::cout << entries.back().endTime;
    }

    std::cout << "\n";
}

void GanttChart::clear() {
    entries.clear();
}

const std::vector<GanttEntry>&
GanttChart::getEntries() const {
    return entries;
}

int GanttChart::getBusyTime() const {

    int busyTime = 0;

    for (const auto& entry : entries) {

        if (entry.pid != -1) {

            busyTime +=
                entry.endTime -
                entry.startTime;
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

    return
        getSimulationEnd() -
        getSimulationStart();
}

int GanttChart::getIdleTime() const {

    return
        getElapsedTime() -
        getBusyTime();
}

int GanttChart::getContextSwitchCount() const {

    if (entries.size() <= 1) {
        return 0;
    }

    int contextSwitches = 0;

    for (size_t i = 1; i < entries.size(); ++i) {

        const auto& previous =
            entries[i - 1];

        const auto& current =
            entries[i];

        /*
         * IDLE -> process is not counted as a
         * process-to-process context switch.
         *
         * Process -> IDLE is also not counted.
         */
        if (
            previous.pid != -1 &&
            current.pid != -1 &&
            previous.pid != current.pid
        ) {
            ++contextSwitches;
        }
    }

    return contextSwitches;
}
