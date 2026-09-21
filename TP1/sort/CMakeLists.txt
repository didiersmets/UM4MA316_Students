cmake_minimum_required(VERSION 3.0)
project(TP1
    VERSION 1.0.0
    LANGUAGES C
)

# C settings
set(CMAKE_C_STANDARD 11)


# c code
add_executable(bubble_insertion_sort
    src/bubble_insertion_sort.c
)
