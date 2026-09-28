#include <stdlib.h>
#include <assert.h>

#include "../include/meshes.h"

int initialize_mesh2D(Mesh2D *m, int vtx_capacity, int tri_capacity)
{
    m->nv = 0;
    m->nt = 0;
    m->vert = (Vertex *)malloc(vtx_capacity * sizeof(Vertex));
    m->tri = (Triangle *)malloc(tri_capacity * sizeof(Triangle));
    if (m->vert == NULL || m->tri == NULL) return EXIT_FAILURE; 
    return EXIT_SUCCESS;
}

void dispose_mesh2D(Mesh2D *m)
{
    if (m==NULL){
        return;
    }

    free(m->vert);
    free(m->tri);
    free(m);
}

double area_mesh2D(Mesh2D *m)
{
    double areaTot = 0.0;

    if(m->vert == NULL || m->tri == NULL){
        return 0.0;
    }
    for(int i=0; i<m->nt; i++){
        areaTot += tri_area(m->vert[m->tri[i].na], m->vert[m->tri[i].nb], m->vert[m->tri[i].nc]);
    }

    return areaTot;
}

double tri_area(Vertex v1, Vertex v2, Vertex v3)
{
    return 0.5 * (v1.x * (v2.y - v3.y) + v2.x * (v3.y - v1.y) + v3.x * (v1.y - v2.y));
}