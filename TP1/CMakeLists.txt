cmake_minimum_required(VERSION 3.0)
project(TP1
    VERSION 1.0.0
    LANGUAGES C CXX
)

# C settings
set(CMAKE_C_STANDARD 11)
# C++ settings
set(CMAKE_CXX_STANDARD 17)

# c code
add_executable(c_test
    c_src/circular_buffer_queue.c
    c_src/test_queue.c
)
# tell where the includes are
target_include_directories(c_test PRIVATE c_src/include)


# c++ code
add_executable(cpp_test
    cpp_src/test_queue.cpp # your C++ test runner / main
)
target_include_directories(cpp_test PRIVATE cpp_src/include)

