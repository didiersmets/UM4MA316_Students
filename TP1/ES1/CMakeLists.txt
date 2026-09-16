cmake_minimum_required(VERSION 3.16)

project(CircularBuffer C)

add_compile_options(-Wall -Wextra -g)

add_executable(test_queue 
    src/circular_buffer_queue.c 
    src/test_queue.c
)

target_include_directories(test_queue PRIVATE ${CMAKE_SOURCE_DIR}/include)