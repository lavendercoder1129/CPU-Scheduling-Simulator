#include "WorkloadManager.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>


bool WorkloadManager::saveToCSV(
    const std::string& filename,
    const std::vector<Process>& processes) {

    std::ofstream file(filename);

    if (!file.is_open()) {

        std::cerr
            << "Error: Could not open file for writing: "
            << filename
            << "\n";

        return false;
    }

    file << "PID,ArrivalTime,BurstTime,Priority\n";

    for (const auto& process : processes) {

        file
            << process.getPid() << ","
            << process.getArrivalTime() << ","
            << process.getBurstTime() << ","
            << process.getPriority()
            << "\n";
    }

    return true;
}


std::vector<Process> WorkloadManager::loadFromCSV(
    const std::string& filename) {

    std::ifstream file(filename);

    if (!file.is_open()) {

        throw std::runtime_error(
            "Could not open workload file: " + filename
        );
    }

    std::vector<Process> processes;

    std::string line;

    // Skip header
    std::getline(file, line);

    while (std::getline(file, line)) {

        if (line.empty())
            continue;

        std::stringstream ss(line);

        std::string value;

        int pid;
        int arrivalTime;
        int burstTime;
        int priority;


        // PID
        if (!std::getline(ss, value, ',')) {
            throw std::runtime_error(
                "Invalid CSV format."
            );
        }

        pid = std::stoi(value);


        // Arrival Time
        if (!std::getline(ss, value, ',')) {
            throw std::runtime_error(
                "Invalid CSV format."
            );
        }

        arrivalTime = std::stoi(value);


        // Burst Time
        if (!std::getline(ss, value, ',')) {
            throw std::runtime_error(
                "Invalid CSV format."
            );
        }

        burstTime = std::stoi(value);


        // Priority
        if (!std::getline(ss, value, ',')) {
            throw std::runtime_error(
                "Invalid CSV format."
            );
        }

        priority = std::stoi(value);


        if (arrivalTime < 0) {

            throw std::runtime_error(
                "Arrival time cannot be negative."
            );
        }

        if (burstTime <= 0) {

            throw std::runtime_error(
                "Burst time must be greater than zero."
            );
        }

        if (priority <= 0) {

            throw std::runtime_error(
                "Priority must be greater than zero."
            );
        }


        processes.emplace_back(
            pid,
            arrivalTime,
            burstTime,
            priority
        );
    }

    if (processes.empty()) {

        throw std::runtime_error(
            "CSV file contains no processes."
        );
    }

    return processes;
}
