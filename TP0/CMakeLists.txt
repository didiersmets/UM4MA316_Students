cmake_minimum_required(VERSION 3.0)
project(TP0)

add_executable(2_hello_make_compiled 2_hello.c)

add_executable(3_pascal 3_pascal.c)
add_executable(3_2_pascal 3_2_pascal.c)


add_executable(4_read_file 4_read_file.c)
add_executable(4_write_file 4_write_file.c)
target_link_libraries(4_write_file PRIVATE m) #for linking math.h
add_executable(4_2_write_file 4_2_write_file.c)
target_link_libraries(4_2_write_file PRIVATE m) #for linking math.h