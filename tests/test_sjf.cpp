#include <gtest/gtest.h>

#include "SJFScheduler.h"
#include "SchedulingResult.h"

#include <vector>


TEST(SJFTest, SelectsShortestAvailableProcess) {

    std::vector<Process> processes;

    processes.emplace_back(1, 0, 7, 1);
    processes.emplace_back(2, 0, 2, 2);
    processes.emplace_back(3, 0, 4, 3);

    SJFScheduler scheduler;

    SchedulingResult result =
        scheduler.schedule(processes);

    const auto& entries =
        result.getGanttChart().getEntries();


    ASSERT_EQ(entries.size(), 3);


    EXPECT_EQ(entries[0].pid, 2);
    EXPECT_EQ(entries[1].pid, 3);
    EXPECT_EQ(entries[2].pid, 1);


    EXPECT_EQ(entries[0].startTime, 0);
    EXPECT_EQ(entries[0].endTime, 2);

    EXPECT_EQ(entries[1].startTime, 2);
    EXPECT_EQ(entries[1].endTime, 6);

    EXPECT_EQ(entries[2].startTime, 6);
    EXPECT_EQ(entries[2].endTime, 13);
}
