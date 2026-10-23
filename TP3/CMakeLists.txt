cmake_minimum_required(VERSION 3.15)

project(TP3 C)

add_executable(time_tables
  src/tp3.c 
  src/mesh_adjacency.c  
  src/hash_tables.c 
  src/mesh_io.c 
  src/mesh.c  
)

target_include_directories(time_tables PRIVATE include)
