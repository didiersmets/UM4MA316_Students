cmake_minimum_required(VERSION 3.15)

project(TP4 C)

add_executable(test_prio_queue
  src/prio_queue.c  
  src/main.c  
)

target_include_directories(test_prio_queue PRIVATE include)

