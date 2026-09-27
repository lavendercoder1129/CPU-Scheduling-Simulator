#ifndef STATISTICS_DISPLAY_H
#define STATISTICS_DISPLAY_H

#include "Statistics.h"
#include "Process.h"

#include <vector>

class StatisticsDisplay {

public:

    static void display(
        const SchedulingStatistics& stats
    );

    static void displayProcessMetrics(
        const std::vector<Process>& processes
    );
};

#endif
