#include <gtest/gtest.h>

#include "MLFQScheduler.h"
#include "SchedulingResult.h"

#include <vector>


TEST(MLFQTest, ProcessMovesBetweenQueues) {

    std::vector<Process> processes;

    processes.emplace_back(1, 0, 8, 1);
    processes.emplace_back(2, 0, 2, 2);

    MLFQScheduler scheduler;

    SchedulingResult result =
        scheduler.schedule(processes);

    const auto& entries =
        result.getGanttChart().getEntries();


    ASSERT_FALSE(entries.empty());


    // P1 initially receives Queue 0 quantum = 2
    EXPECT_EQ(entries[0].pid, 1);
    EXPECT_EQ(entries[0].startTime, 0);
    EXPECT_EQ(entries[0].endTime, 2);


    // P2 arrives initially and receives Queue 0
    EXPECT_EQ(entries[1].pid, 2);
    EXPECT_EQ(entries[1].startTime, 2);
    EXPECT_EQ(entries[1].endTime, 4);
}
