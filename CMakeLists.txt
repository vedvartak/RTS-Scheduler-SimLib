cmake_minimum_required(VERSION 3.30)
project(RTSSchedulerSimLib)
set(CMAKE_CXX_STANDARD 17 CACHE STRING "CXX standard to be used. (minimum 17)")

# Building RTS library
set(SRC_CORE src/taskmanager.cpp src/scheduler.cpp src/timer.cpp)
set(SRC_ALGORITHMS src/algorithms/rma.cpp src/algorithms/dma.cpp src/algorithms/edf.cpp src/algorithms/lst.cpp)
set(INCLUDE_DIRS includes/)
add_library(RTSsimLib ${SRC_CORE} ${SRC_ALGORITHMS})
target_include_directories(RTSsimLib PUBLIC ${INCLUDE_DIRS})

# Building Tests
file(GLOB test_files LIST_DIRECTORIES false RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} test/*.cpp)
message(STATUS "BUILDING TESTS")
foreach(test_src ${test_files})
    cmake_path(GET test_src STEM test_target)
    message(VERBOSE "TEST: ${test_target} (${test_src})")
    add_executable(${test_target} ${test_src})
    target_link_libraries(${test_target} PUBLIC RTSsimLib)
endforeach(test_src ${test_files})

