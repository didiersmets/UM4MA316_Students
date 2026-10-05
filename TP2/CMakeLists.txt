cmake_minimum_required(VERSION 3.15)

project(TP2 C)

add_executable(mesh_manip
  src/main.c 
  src/mesh.c 
)


target_include_directories(mesh_manip PRIVATE include)
