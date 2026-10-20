#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "mesh.h"
#include "mesh_io.h"
#include "mesh_adjacency.h"

static double seconds(void){
    return (double)clock() / CLOCKS_PER_SEC;
}

int main(int argc, char* argv[]){

    if(argc < 2){
        fprintf(stderr, "Error, filename missing!");
        return 1;
    }

    struct Mesh m;
    initialize_mesh(&m);

    if(read_mesh_from_wavefront_file(&m,argv[1]) == -1){
        fprintf(stderr,"Error reading the wavefront file!");
        return 1;
    }
    printf("%s: %d vertices, %d triangles\n\n",argv[1],m.nvert,m.ntri);

    double t;
    int *adj1 = NULL;

    if(!strstr(argv[1], "bugatti")){
        t = seconds();
        adj1 = build_adjacency_table1(&m);
        printf("Method 1:      %.6f s\n", seconds() - t);
    }

    t = seconds();
    int *adj2 = build_adjacency_table2(&m);
    printf("Method 2:      %.6f s\n", seconds() - t);

    t = seconds();
    int *adj3 = build_adjacency_table3(&m);
    printf("Method 3:      %.6f s\n", seconds() - t);

    free(adj1);
    free(adj2);
    free(adj3);
    dispose_mesh(&m);
    return 0;
}