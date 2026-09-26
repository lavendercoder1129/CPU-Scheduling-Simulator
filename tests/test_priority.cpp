#include <gtest/gtest.h>

#include "PriorityScheduler.h"
#include "SchedulingResult.h"

#include <vector>


TEST(PriorityTest, SelectsHighestPriorityProcess) {

    std::vector<Process> processes;

    processes.emplace_back(1, 0, 5, 3);
    processes.emplace_back(2, 0, 2, 1);
    processes.emplace_back(3, 0, 4, 2);

    PriorityScheduler scheduler;

    SchedulingResult result =
        scheduler.schedule(processes);

    const auto& entries =
        result.getGanttChart().getEntries();


    ASSERT_EQ(entries.size(), 3);


    // Lower number = higher priority
    EXPECT_EQ(entries[0].pid, 2);
    EXPECT_EQ(entries[1].pid, 3);
    EXPECT_EQ(entries[2].pid, 1);
}
