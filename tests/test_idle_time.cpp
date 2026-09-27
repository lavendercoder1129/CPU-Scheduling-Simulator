#include <gtest/gtest.h>

#include "FCFSScheduler.h"
#include "SchedulingResult.h"

TEST(IdleTimeTest, DetectsInitialCPUIdleTime) {
    std::vector<Process> processes;

    processes.emplace_back(1, 5, 3, 1);

    FCFSScheduler scheduler;

    SchedulingResult result = scheduler.schedule(processes);

    const auto& entries = result.getGanttChart().getEntries();

    ASSERT_EQ(entries.size(), 2);

    EXPECT_EQ(entries[0].pid, -1);
    EXPECT_EQ(entries[0].startTime, 0);
    EXPECT_EQ(entries[0].endTime, 5);

    EXPECT_EQ(entries[1].pid, 1);
    EXPECT_EQ(entries[1].startTime, 5);
    EXPECT_EQ(entries[1].endTime, 8);

    EXPECT_EQ(
        result.getGanttChart().getBusyTime(),
        3
    );

    EXPECT_EQ(
        result.getGanttChart().getIdleTime(),
        5
    );

    EXPECT_EQ(
        result.getGanttChart().getElapsedTime(),
        8
    );
}
