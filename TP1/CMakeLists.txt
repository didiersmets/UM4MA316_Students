cmake_minimum_required(VERSION 3.15)
project(TP1 LANGUAGES C CXX)

add_executable(test_queue_c src/test_queue.c src/circular_buffer_queue.c)
target_include_directories(test_queue_c PRIVATE include)

add_executable(test_queue_cpp src/test_queue.cpp)
target_include_directories(test_queue_cpp PRIVATE include)

add_executable(sorting ex2/sorting.c)