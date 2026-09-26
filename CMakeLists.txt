cmake_minimum_required(VERSION 3.16)

project(CPUSchedulingSimulator)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(CPUSchedulingSimulator
    main.cpp
    src/Process.cpp
    src/FCFSScheduler.cpp
    src/GanttChart.cpp
    src/SJFScheduler.cpp
    src/PriorityScheduler.cpp
    src/RRScheduler.cpp
)

target_include_directories(CPUSchedulingSimulator
    PRIVATE
    ${PROJECT_SOURCE_DIR}/include
)
