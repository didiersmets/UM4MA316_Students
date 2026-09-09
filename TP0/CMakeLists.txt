cmake_minimum_required(VERSION 3.15)
project(TP0 C)

add_executable(tp0
    hello.c
)

target_include_directories(tp0 PRIVATE include)