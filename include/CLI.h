#ifndef CLI_H
#define CLI_H

#include "Process.h"

#include <vector>

class CLI {

public:

    static void displayMainMenu();

    static int getMenuChoice();

    static std::vector<Process> inputProcesses();

    static std::vector<Process> generateSampleWorkload();

    static int getTimeQuantum();

};

#endif
