#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "mesh.h"
#include "mesh_io.h"
#include "mesh_adjacency.h"

int main(int argc, char **argv){

    const char *filename = argv[1];
    struct Mesh m;
    initialize_mesh(&m);
    int status;
    status = read_mesh_from_wavefront_file(&m, filename);

    printf("vertexs : %d \n", m.nvert);
    printf("triangles : %d\n", m.ntri);

    clock_t start, end;
    int *adj1 = NULL;
    int *adj2 = NULL;
    int *adj3 = NULL;

    if (strcmp(filename, "data/bugatti.obj")){
        start = clock();
        adj1 = build_adjacency_table1(&m);
        end = clock();
        printf("Method 1: %f s\n", (double)(end - start) / CLOCKS_PER_SEC);
    }

    start = clock();
    adj2 = build_adjacency_table2(&m);
    end = clock();
    printf("Method 2: %f s\n", (double)(end - start) / CLOCKS_PER_SEC);

    start = clock();
    adj3 = build_adjacency_table3(&m);
    end = clock();

    printf("Method 3: %f s\n", (double)(end - start) / CLOCKS_PER_SEC);

    free(adj1);
    free(adj2);
    free(adj3);
    dispose_mesh(&m);

    return 0;
}
