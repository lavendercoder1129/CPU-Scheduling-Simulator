#include <gtest/gtest.h>

#include "RRScheduler.h"
#include "SchedulingResult.h"

#include <vector>


TEST(RoundRobinTest, RespectsTimeQuantum) {

    std::vector<Process> processes;

    processes.emplace_back(1, 0, 5, 1);
    processes.emplace_back(2, 0, 3, 2);

    RRScheduler scheduler(2);

    SchedulingResult result =
        scheduler.schedule(processes);

    const auto& entries =
        result.getGanttChart().getEntries();


    // Expected execution:
    //
    // P1: 0-2
    // P2: 2-4
    // P1: 4-6
    // P2: 6-7
    // P1: 7-8

    ASSERT_EQ(entries.size(), 5);


    EXPECT_EQ(entries[0].pid, 1);
    EXPECT_EQ(entries[0].startTime, 0);
    EXPECT_EQ(entries[0].endTime, 2);


    EXPECT_EQ(entries[1].pid, 2);
    EXPECT_EQ(entries[1].startTime, 2);
    EXPECT_EQ(entries[1].endTime, 4);


    EXPECT_EQ(entries[2].pid, 1);
    EXPECT_EQ(entries[2].startTime, 4);
    EXPECT_EQ(entries[2].endTime, 6);


    EXPECT_EQ(entries[3].pid, 2);
    EXPECT_EQ(entries[3].startTime, 6);
    EXPECT_EQ(entries[3].endTime, 7);


    EXPECT_EQ(entries[4].pid, 1);
    EXPECT_EQ(entries[4].startTime, 7);
    EXPECT_EQ(entries[4].endTime, 8);
}
