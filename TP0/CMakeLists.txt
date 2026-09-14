cmake_minimum_required(VERSION 3.16)
project(tp0 C)

add_executable(hello hello.c)

add_executable(es3 es3.c)
add_executable(es3_dynamic es3_dynamic_allocation.c)

add_executable(es4_0 es4_0.c)

add_executable(es4_1 es4_1.c)
target_link_libraries(es4_1 PRIVATE m)
add_executable(es4_1_dynamic es4_1_dynamic_allocation.c)
target_link_libraries(es4_1_dynamic PRIVATE m)