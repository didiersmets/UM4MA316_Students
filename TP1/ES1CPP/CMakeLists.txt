cmake_minimum_required(VERSION 3.16)

project(CircularBufferCPP CXX)

add_compile_options(-Wall -Wextra -g)

add_executable(test_queue src/test_queue.cpp)

target_include_directories(test_queue PRIVATE ${CMAKE_SOURCE_DIR}/include)