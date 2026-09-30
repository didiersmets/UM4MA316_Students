#ifndef MESHES_3D_H
#define MESHES_3D_H

#include <stdlib.h>

typedef struct 
{
    double x;
    double y;
    double z;
}Vertex3D;

typedef struct
{
    int na;
    int nb;
    int nc;
}Triangle;

typedef struct 
{
    int nv;
    Vertex3D *vert;
    int nt;
    Triangle *tri;
}Mesh3D;

int initialize_Mesh3D(Mesh3D *m, int vtx_capacity, int tri_capacity);


void dispose_Mesh3D(Mesh3D *m);

Vertex3D CrossProduct(Vertex3D v1, Vertex3D v2);

double Magnitude(Vertex3D v1);

double tri_area3D(Vertex3D v1, Vertex3D v2, Vertex3D v3);

Vertex3D NormalArea(Vertex3D v1, Vertex3D v2, Vertex3D v3);

double Surface_Mesh3D(Mesh3D *m);

double ScalarProduct(Vertex3D v1, Vertex3D v2);

Vertex3D Baricenter(Vertex3D v1, Vertex3D v2, Vertex3D v3);

double Volume_closed_Mesh3D(Mesh3D *m);

#endif