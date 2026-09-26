#include <iostream>
#include <vector>

#include "Process.h"
#include "Scheduler.h"

class TestScheduler : public Scheduler {
public:

    void schedule(std::vector<Process>& processes) override {
        std::cout << "Test scheduler executed.\n";
    }

    void displayResults(
        const std::vector<Process>& processes
    ) const override {
        std::cout << "Displaying results.\n";
    }
};

int main() {

    std::vector<Process> processes;

    processes.emplace_back(1, 0, 5, 2);
    processes.emplace_back(2, 1, 3, 1);

    TestScheduler scheduler;

    scheduler.schedule(processes);
    scheduler.displayResults(processes);

    return 0;
}
