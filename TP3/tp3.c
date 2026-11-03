#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "mesh_adjacency.h"
#include "mesh_io.h"
#include "mesh.h"
#include "hash_tables.h"

double get_wall_time() {
    struct timespec time;
    clock_gettime(CLOCK_MONOTONIC, &time);
    return (double)time.tv_sec + (double)time.tv_nsec * 1e-9;
}


int main(int argc, char *argv[]){


    int *at1, *at2, *at3;
    struct Mesh m;
    initialize_mesh(&m);

    const char *path = argc > 1 ? argv[1] : "data/bunny.obj";
    if (read_mesh_from_wavefront_file(&m, path) != 0) {
        fprintf(stderr, "cannot read %s\n", path);
        return 1;
    }

    // --- TIMING ---

    double start_1 = get_wall_time();
    at1 = build_adjacency_table1(&m);
    double end_1 = get_wall_time();

    double start_2 = get_wall_time();
    at2 = build_adjacency_table2(&m);
    double end_2 = get_wall_time();

    double start_3 = get_wall_time();
    at3 = build_adjacency_table3(&m);
    double end_3 = get_wall_time();

    double time_1 = end_1 - start_1;
    double time_2 = end_2 - start_2;
    double time_3 = end_3 - start_3;

    printf(" --- Time for building adjacency tables ----\n");
    printf("table1: %lf \n", time_1);
    printf("table2: %lf \n", time_2);
    printf("table3: %lf \n", time_3);

    free(at1); free(at2); free(at3);
    dispose_mesh(&m);

    





    // --- TESTS ---
    printf("----- TESTS -----\n");
    
    struct Mesh sq;
    initialize_mesh(&sq);

    sq.nvert = 4;
    sq.vertices = malloc(sq.nvert * sizeof(struct Vertex));
    sq.vertices[0].x = 0; sq.vertices[0].y = 0; sq.vertices[0].z = 0;
    sq.vertices[1].x = 1; sq.vertices[1].y = 0; sq.vertices[1].z = 0;
    sq.vertices[2].x = 1; sq.vertices[2].y = 1; sq.vertices[2].z = 0;
    sq.vertices[3].x = 0; sq.vertices[3].y = 1; sq.vertices[3].z = 0;

    sq.ntri = 2;
    sq.triangles = malloc(sq.ntri * sizeof(struct Triangle));
    sq.triangles[0].v1 = 0; sq.triangles[0].v2 = 1; sq.triangles[0].v3 = 2;
    sq.triangles[1].v1 = 0; sq.triangles[1].v2 = 2; sq.triangles[1].v3 = 3;


    int edge = tris_are_neighbors(0,1, &sq);
    printf("Triangles are neighbours on edge of t1 no: %d \n", edge);

    int *adjacency_table = build_adjacency_table1(&sq);
    for(int i = 0; i < sq.ntri * 3; i++){
        printf("%d ",adjacency_table[i]);
    }
    printf("\n");




    struct Triangle my_triangle;
    my_triangle.v1 = 3;
    my_triangle.v2 = 4;
    my_triangle.v3 = 5;

    int pos = edge_pos_in_tri(3,4,my_triangle);

    printf("Edge Position: %d \n", pos);

    free(adjacency_table);
    dispose_mesh(&sq);
    return 0;
}