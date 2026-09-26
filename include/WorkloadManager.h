#ifndef WORKLOAD_MANAGER_H
#define WORKLOAD_MANAGER_H

#include "Process.h"

#include <string>
#include <vector>

class WorkloadManager {

public:

    static bool saveToCSV(
        const std::string& filename,
        const std::vector<Process>& processes
    );

    static std::vector<Process> loadFromCSV(
        const std::string& filename
    );
};

#endif
