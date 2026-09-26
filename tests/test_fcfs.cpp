#include <gtest/gtest.h>

#include "FCFSScheduler.h"
#include "SchedulingResult.h"

#include <vector>


TEST(FCFSTest, CalculatesCompletionTimes) {

    std::vector<Process> processes;

    processes.emplace_back(1, 0, 5, 1);
    processes.emplace_back(2, 1, 3, 2);
    processes.emplace_back(3, 2, 2, 3);

    FCFSScheduler scheduler;

    SchedulingResult result =
        scheduler.schedule(processes);

    const auto& scheduled =
        result.getProcesses();


    EXPECT_EQ(scheduled[0].getCompletionTime(), 5);
    EXPECT_EQ(scheduled[1].getCompletionTime(), 8);
    EXPECT_EQ(scheduled[2].getCompletionTime(), 10);
}


TEST(FCFSTest, CalculatesWaitingTimes) {

    std::vector<Process> processes;

    processes.emplace_back(1, 0, 5, 1);
    processes.emplace_back(2, 1, 3, 2);

    FCFSScheduler scheduler;

    SchedulingResult result =
        scheduler.schedule(processes);

    const auto& scheduled =
        result.getProcesses();


    EXPECT_EQ(scheduled[0].getWaitingTime(), 0);

    EXPECT_EQ(scheduled[1].getWaitingTime(), 4);
}
