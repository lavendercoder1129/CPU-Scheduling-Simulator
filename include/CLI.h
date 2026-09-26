#ifndef CLI_H
#define CLI_H

#include "Process.h"

#include <string>
#include <vector>

class CLI {

public:

    static void displayMainMenu();

    static int getMenuChoice();

    static std::vector<Process> inputProcesses();

    static std::vector<Process> generateSampleWorkload();

    static std::vector<Process> loadWorkload();

    static int getTimeQuantum();
};

#endif
