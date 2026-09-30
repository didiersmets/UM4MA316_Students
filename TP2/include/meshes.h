#ifndef MESHES_H
#define MESHES_H

#include <stdlib.h>

typedef struct 
{
    double x;
    double y;
}Vertex;

typedef struct
{
    int na;
    int nb;
    int nc;
}Triangle;

typedef struct 
{
    int nv;
    Vertex *vert;
    int nt;
    Triangle *tri;
}Mesh2D;

int initialize_mesh2D(Mesh2D *m, int vtx_capacity, int tri_capacity);

void dispose_mesh2D(Mesh2D *m);

double tri_area(Vertex v1, Vertex v2, Vertex v3);

double area_mesh2D(Mesh2D *m);

int read_mesh2D(Mesh2D *m, const char *filename);

int mesh2D_to_gnuplot(Mesh2D *m, const char *filename);

int write_mesh2D(Mesh2D *m, const char *filename);

#endif