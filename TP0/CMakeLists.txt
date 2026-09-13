cmake_minimum_required(VERSION 3.13)

project(tp0)

set(CMAKE_C_STANDARD 99)
add_compile_options(-Wall -Wextra -Werror -Wpedantic)

add_executable(hello src/hello.c)
add_executable(read_file src/read_file.c)
add_executable(pascal_triangle src/pascal_triangle.c)

# target_compile_features(hello PRIVATE c_std_99)
# target_compile_options(hello PRIVATE -Wall -Wextra -Werror)
