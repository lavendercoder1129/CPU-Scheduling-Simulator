#include "CLI.h"

#include <iostream>
#include <limits>
#include <vector>


void CLI::displayMainMenu() {

    std::cout << "\n";
    std::cout
        << "========================================\n";

    std::cout
        << "       CPU SCHEDULING SIMULATOR\n";

    std::cout
        << "========================================\n";

    std::cout
        << "1. Enter processes manually\n";

    std::cout
        << "2. Generate sample workload\n";

    std::cout
        << "3. Exit\n";

    std::cout
        << "========================================\n";
}


int CLI::getMenuChoice() {

    int choice;

    while (true) {

        std::cout << "Enter choice: ";

        if (std::cin >> choice &&
            choice >= 1 &&
            choice <= 3) {

            return choice;
        }

        std::cout
            << "Invalid choice. "
            << "Please enter 1, 2, or 3.\n";

        std::cin.clear();

        std::cin.ignore(
            std::numeric_limits<std::streamsize>::max(),
            '\n'
        );
    }
}


std::vector<Process> CLI::inputProcesses() {

    int n;

    while (true) {

        std::cout
            << "\nEnter number of processes: ";

        if (std::cin >> n && n > 0) {
            break;
        }

        std::cout
            << "Number of processes must be greater than 0.\n";

        std::cin.clear();

        std::cin.ignore(
            std::numeric_limits<std::streamsize>::max(),
            '\n'
        );
    }


    std::vector<Process> processes;

    for (int i = 0; i < n; i++) {

        int arrivalTime;
        int burstTime;
        int priority;

        std::cout
            << "\nProcess P"
            << (i + 1)
            << "\n";


        while (true) {

            std::cout
                << "Arrival Time: ";

            if (
                std::cin >> arrivalTime &&
                arrivalTime >= 0
            ) {
                break;
            }

            std::cout
                << "Arrival time must be >= 0.\n";

            std::cin.clear();

            std::cin.ignore(
                std::numeric_limits<std::streamsize>::max(),
                '\n'
            );
        }


        while (true) {

            std::cout
                << "Burst Time: ";

            if (
                std::cin >> burstTime &&
                burstTime > 0
            ) {
                break;
            }

            std::cout
                << "Burst time must be > 0.\n";

            std::cin.clear();

            std::cin.ignore(
                std::numeric_limits<std::streamsize>::max(),
                '\n'
            );
        }


        while (true) {

            std::cout
                << "Priority (lower = higher): ";

            if (
                std::cin >> priority &&
                priority > 0
            ) {
                break;
            }

            std::cout
                << "Priority must be > 0.\n";

            std::cin.clear();

            std::cin.ignore(
                std::numeric_limits<std::streamsize>::max(),
                '\n'
            );
        }


        processes.emplace_back(
            i + 1,
            arrivalTime,
            burstTime,
            priority
        );
    }

    return processes;
}


std::vector<Process>
CLI::generateSampleWorkload() {

    std::vector<Process> processes;

    processes.emplace_back(
        1, 0, 8, 3
    );

    processes.emplace_back(
        2, 1, 4, 1
    );

    processes.emplace_back(
        3, 2, 2, 4
    );

    processes.emplace_back(
        4, 3, 6, 2
    );

    return processes;
}


int CLI::getTimeQuantum() {

    int quantum;

    while (true) {

        std::cout
            << "\nEnter Round Robin time quantum: ";

        if (
            std::cin >> quantum &&
            quantum > 0
        ) {

            return quantum;
        }

        std::cout
            << "Time quantum must be greater than 0.\n";

        std::cin.clear();

        std::cin.ignore(
            std::numeric_limits<std::streamsize>::max(),
            '\n'
        );
    }
}
