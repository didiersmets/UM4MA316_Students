cmake_minimum_required(VERSION 3.16)
project(TP3 C)


add_executable(tp3
    src/tp3.c
    src/mesh.c
    src/mesh_io.c
    src/mesh_adjacency.c
    src/hash_tables.c
)

target_include_directories(tp3 PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)