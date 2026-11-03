cmake_minimum_required(VERSION 3.16)
project(TP4 C)

set(CMAKE_C_STANDARD 11)

add_executable(tp4
    src/main.c
    src/priority.c
    src/tree.c
)

target_include_directories(tp4 PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
