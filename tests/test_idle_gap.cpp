#include <gtest/gtest.h>

#include "FCFSScheduler.h"
#include "SchedulingResult.h"

TEST(IdleTimeTest, DetectsIdleGapBetweenProcesses) {

    std::vector<Process> processes;

    processes.emplace_back(1, 0, 3, 1);
    processes.emplace_back(2, 8, 2, 2);

    FCFSScheduler scheduler;

    SchedulingResult result =
        scheduler.schedule(processes);

    const auto& entries =
        result.getGanttChart().getEntries();

    ASSERT_EQ(entries.size(), 3);

    // P1: 0 - 3
    EXPECT_EQ(entries[0].pid, 1);
    EXPECT_EQ(entries[0].startTime, 0);
    EXPECT_EQ(entries[0].endTime, 3);

    // CPU idle: 3 - 8
    EXPECT_EQ(entries[1].pid, -1);
    EXPECT_EQ(entries[1].startTime, 3);
    EXPECT_EQ(entries[1].endTime, 8);

    // P2: 8 - 10
    EXPECT_EQ(entries[2].pid, 2);
    EXPECT_EQ(entries[2].startTime, 8);
    EXPECT_EQ(entries[2].endTime, 10);

    EXPECT_EQ(
        result.getGanttChart().getBusyTime(),
        5
    );

    EXPECT_EQ(
        result.getGanttChart().getIdleTime(),
        5
    );

    EXPECT_EQ(
        result.getGanttChart().getElapsedTime(),
        10
    );
}
