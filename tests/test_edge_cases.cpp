#include <gtest/gtest.h>

#include "FCFSScheduler.h"
#include "RRScheduler.h"
#include "SchedulingResult.h"

TEST(EdgeCaseTest, SingleProcessFCFS) {

    std::vector<Process> processes;

    processes.emplace_back(1, 0, 5, 1);

    FCFSScheduler scheduler;

    SchedulingResult result =
        scheduler.schedule(processes);

    ASSERT_EQ(
        result.getGanttChart().getEntries().size(),
        1
    );

    const auto& process =
        result.getProcesses()[0];

    EXPECT_EQ(process.getStartTime(), 0);
    EXPECT_EQ(process.getCompletionTime(), 5);
    EXPECT_EQ(process.getTurnaroundTime(), 5);
    EXPECT_EQ(process.getWaitingTime(), 0);
    EXPECT_EQ(process.getResponseTime(), 0);

    EXPECT_EQ(
        result.getContextSwitches(),
        0
    );
}


TEST(EdgeCaseTest, SingleProcessRoundRobin) {

    std::vector<Process> processes;

    processes.emplace_back(1, 0, 5, 1);

    RRScheduler scheduler(2);

    SchedulingResult result =
        scheduler.schedule(processes);

    const auto& entries =
        result.getGanttChart().getEntries();

    ASSERT_EQ(entries.size(), 3);

    EXPECT_EQ(entries[0].startTime, 0);
    EXPECT_EQ(entries[0].endTime, 2);

    EXPECT_EQ(entries[1].startTime, 2);
    EXPECT_EQ(entries[1].endTime, 4);

    EXPECT_EQ(entries[2].startTime, 4);
    EXPECT_EQ(entries[2].endTime, 5);

    EXPECT_EQ(
        result.getProcesses()[0].getCompletionTime(),
        5
    );
}
