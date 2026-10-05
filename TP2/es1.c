#include<stdio.h>

typedef struct{
    double x;
    double y;
}Vertex;

typedef struct{
    int a;
    int b;
    int c;
}Triangle;

typedef struct{
    int nv;
    Vertex* vtx;
    int vtx_capacity;
    int nt;
    Triangle* tri;
    int tri_capacity;
}Mesh2D;


//returns 1 if malloc fails. 0 otherwise
int initialize_mesh2D (Mesh2D* m, int vtx_capacity, int tri_capacity){
    m -> nv = 0;
    m -> vtx_capacity = vtx_capacity;
    m -> vtx = malloc(vtx_capacity * sizeof(Vetex));
    if(m->vtx == NULL)
        return 1;

    m -> nt = 0;
    m -> tri_capacity = tri_capacity;

    m -> tri = malloc(tri_capacity * sizeof(Triangle));
    if(m->tri == NULL)
        return 1;

    return 0;
}

void dispose_mesh2D (Mesh2D* m){
    free(m -> vtx);
    free(m -> tri);

    m -> vtx = NULL;
    m -> tri = NULL;

    m -> vtx_capacity = 0;
    m -> tri_capacity = 0;
}


