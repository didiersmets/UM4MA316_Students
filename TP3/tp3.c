#include <stdio.h>
#include <stdlib.h>

#include "mesh_adjacency.h"
#include "mesh_io.h"
#include "mesh.h"
#include "hash_tables.h"




int main(int argc, char **argv[]){


    

    





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


    dispose_mesh(&sq);
    return 0;
}