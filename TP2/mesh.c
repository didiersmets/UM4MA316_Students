#include <stdio.h>
#include <stdlib.h>
#include "mesh.h"

void initialize_mesh2D(struct Mesh2D* m, int vtx_capacity, int tri_capacity){
    struct Mesh2D mesh;
    m->nv = vtx_capacity;
    m->nt = tri_capacity;
    m->vert = malloc(sizeof(struct Vertex)*m->nv);
    m->tri = malloc(sizeof(struct Triangle)*m->nt);
}

void dispose_mesh2D(struct Mesh2D* m){
    free(m->vert);
    free(m->tri);
}

double area_mesh2D(struct Mesh2D* m){
    double sum = 0;
    for (int i=0; i < m->nt; i++){
        struct Vertex A = m->vert[m->tri[i].nA];
        struct Vertex B = m->vert[m->tri[i].nB];
        struct Vertex C = m->vert[m->tri[i].nC];


        double v1x = B.x - A.x;
        double v1y = B.y - A.y;
        double v2x = C.x - A.x;
        double v2y = C.y - A.y;

        double det = v1x*v2y - v2x*v1y;
        
        sum += (1.0/2.0)*det;
    }

    return sum;
}





int main (int argc, char* argv[]){
    return 0;
}


