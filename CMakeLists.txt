cmake_minimum_required(VERSION 3.16)

project(CPUSchedulingSimulator)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

find_package(GTest REQUIRED)

add_executable(SchedulingTests
    tests/test_fcfs.cpp
    tests/test_sjf.cpp
    tests/test_priority.cpp
    tests/test_rr.cpp
    tests/test_mlfq.cpp

    src/Process.cpp
    src/FCFSScheduler.cpp
    src/GanttChart.cpp
    src/SJFScheduler.cpp
    src/PriorityScheduler.cpp
    src/RRScheduler.cpp
    src/MLFQScheduler.cpp
    src/Statistics.cpp
    src/StatisticsDisplay.cpp
    src/SchedulingResult.cpp
)

target_include_directories(SchedulingTests
    PRIVATE
    ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(SchedulingTests
    PRIVATE
    GTest::gtest_main
)

include(GoogleTest)

gtest_discover_tests(SchedulingTests)
