# CPU Scheduling Simulator

A C++17-based CPU Scheduling Simulator that implements and compares
multiple CPU scheduling algorithms using Gantt charts and scheduling
performance metrics.

## Features

- FCFS (First Come First Serve)
- SJF (Shortest Job First - Non-Preemptive)
- Priority Scheduling (Non-Preemptive)
- Round Robin
- Multilevel Feedback Queue (MLFQ)
- Gantt chart visualization
- CPU idle-time tracking
- Waiting, turnaround, and response time calculation
- CPU utilization
- Throughput
- Context-switch calculation
- Algorithm comparison
- Interactive CLI
- CSV workload import
- Input validation
- Automated GoogleTest test suite
- CMake-based build system

## Algorithms

| Algorithm | Type | Scheduling |
|-----------|------|------------|
| FCFS | Non-Preemptive | Arrival Order |
| SJF | Non-Preemptive | Shortest Burst |
| Priority | Non-Preemptive | Highest Priority |
| Round Robin | Preemptive | Time Quantum |
| MLFQ | Preemptive | Multiple Priority Queues |

## Project Structure

```text
CPU-Scheduling-Simulator/
├── include/
│   ├── CLI.h
│   ├── ComparisonEngine.h
│   ├── FCFSScheduler.h
│   ├── GanttChart.h
│   ├── MLFQScheduler.h
│   ├── PriorityScheduler.h
│   ├── Process.h
│   ├── RRScheduler.h
│   ├── Scheduler.h
│   ├── SchedulingResult.h
│   ├── Statistics.h
│   ├── StatisticsDisplay.h
│   ├── SJFScheduler.h
│   └── WorkloadManager.h
│
├── src/
│   ├── CLI.cpp
│   ├── ComparisonEngine.cpp
│   ├── FCFSScheduler.cpp
│   ├── GanttChart.cpp
│   ├── MLFQScheduler.cpp
│   ├── PriorityScheduler.cpp
│   ├── Process.cpp
│   ├── RRScheduler.cpp
│   ├── SchedulingResult.cpp
│   ├── SJFScheduler.cpp
│   ├── Statistics.cpp
│   ├── StatisticsDisplay.cpp
│   └── WorkloadManager.cpp
│
├── tests/
├── workloads/
├── docs/
├── main.cpp
├── CMakeLists.txt
└── README.md

Metrics

For each scheduling algorithm, the simulator calculates:

Completion Time (CT)
Turnaround Time (TAT)
Waiting Time (WT)
Response Time (RT)
Average Waiting Time
Average Turnaround Time
Average Response Time
CPU Utilization
Throughput
Context Switches
CPU Busy Time
CPU Idle Time
Elapsed Simulation Time
Metric formulas
Turnaround Time = Completion Time - Arrival Time

Waiting Time = Turnaround Time - Burst Time

Response Time = First Start Time - Arrival Time

CPU Utilization =
CPU Busy Time / Elapsed Simulation Time × 100
Input Options

The simulator supports three workload sources:

Manual process input
CSV workload
Built-in sample workload
CSV Format
PID,ArrivalTime,BurstTime,Priority
1,0,8,3
2,1,4,1
3,2,2,4
4,3,6,2
Build
Requirements
C++17 compiler
CMake 3.16+
GoogleTest
Build
cmake -S . -B build
cmake --build build
Run
./build/CPUSchedulingSimulator
Run Tests
ctest --test-dir build --output-on-failure

The project uses GoogleTest for automated scheduling algorithm and
edge-case testing.

Example Workflow
1. Enter processes manually
2. Load workload from CSV
3. Use sample workload
4. Exit

The simulator executes the workload using all supported scheduling
algorithms and displays individual results followed by an algorithm
comparison table.

Technologies
C++17
CMake
GoogleTest
STL
Linux
Git/GitHub
Concepts Demonstrated
CPU Scheduling
Process Management
Scheduling Algorithms
Queues
Object-Oriented Programming
Data Structures
File I/O
Exception Handling
Unit Testing
Build Automation
