cmake_minimum_required(VERSION 3.15)

project(sorting_algos C)

add_executable(sorting_algos_cmp
  src/algos.c
  src/main.c
)

target_include_directories(sorting_algos_cmp PRIVATE include)

