cmake_minimum_required(VERSION 3.15)

project(circular_buffer C)

add_executable(circular_buffer
  src/test_queue.c
  src/circular_buffer_queue.c
)

target_include_directories(circular_buffer PRIVATE include)
