
#include "mesh_io.h"

#include <stdio.h>   // Used for fopen, fclose, fgets, sscanf and printf
#include <stdlib.h>  // Used for malloc and free
#include <string.h>  // Used for strcmp

#include "mesh.h"

int edge_pos_in_tri(int v1, int v2, struct Triangle t){
    if (t.v1==v1 && t.v2==v2){return 0;}
    if (t.v2==v1 && t.v3==v2){return 1;}
    if (t.v3==v1 && t.v1==v2){return 2;}
    return -1;
}

int tris_are_neighbors(int tri1, int tri2, const struct Mesh *m){
    int i;
    int j;
    struct Triangle t1 = m->triangles[tri1];
    struct Triangle t2 = m->triangles[tri2];

    if (edge_pos_in_tri(t1.v2, t1.v1, t2) != -1){return 0;}
    if (edge_pos_in_tri(t1.v3, t1.v2, t2) != -1){return 1;}
    if (edge_pos_in_tri(t1.v1, t1.v3, t2) != -1){return 2;}

    return -1;
}

int *build_adjacency_table1(const struct Mesh *m){
    int * adj = malloc(sizeof(int)*(3 * m->ntri));
    for (int i = 0; i < 3*(m->ntri); i++){ adj[i] = -1;}

    for (int t1 = 0; t1 < m->ntri; t1++){
        for (int t2 = 0; t2 < m->ntri; t2++){
            int res = tris_are_neighbors(t1, t2, m);
            if(res != -1){
                adj[3*t1 + res] = t2;
            }
        }
    }
    return adj;
}







