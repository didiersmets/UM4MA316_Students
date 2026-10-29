cmake_minimum_required(VERSION 3.10)
project(TP1
    VERSION 1.0.0
    LANGUAGES C
)

# C settings
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

#shared code gets compiled into a library file
add_library(mesh_lib
    src/mesh.c
    src/mesh_io.c
    src/mesh_adjacency.c
    src/hash_tables.c
)

# tell where the includes are
target_include_directories(mesh_lib PUBLIC include)
target_compile_options(mesh_lib PRIVATE -Wall -Wextra)


# c code
add_executable(tp3
    tp3.c
)
target_link_libraries(tp3 PRIVATE mesh_lib)
target_compile_options(tp3 PRIVATE -Wall -Wextra)



