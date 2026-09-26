#include <iostream>
#include "Process.h"

int main() {

    Process p1(1, 0, 5, 2);

    p1.setStartTime(0);
    p1.setCompletionTime(5);

    std::cout << "Turnaround Time: "
              << p1.getTurnaroundTime() << '\n';

    std::cout << "Waiting Time: "
              << p1.getWaitingTime() << '\n';

    std::cout << "Response Time: "
              << p1.getResponseTime() << '\n';

    return 0;
}
