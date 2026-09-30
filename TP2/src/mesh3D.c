#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include "../include/meshes3D.h"

int initialize_Mesh3D(Mesh3D *m, int vtx_capacity, int tri_capacity)
{
    m->nv = 0;
    m->nt = 0;
    m->vert = (Vertex3D *)malloc(vtx_capacity * sizeof(Vertex3D));
    m->tri = (Triangle *)malloc(tri_capacity * sizeof(Triangle));
    if (m->vert == NULL || m->tri == NULL) return EXIT_FAILURE; 
    return EXIT_SUCCESS;
}

void dispose_Mesh3D(Mesh3D *m)
{
    if (m==NULL){
        return;
    }

    free(m->vert);
    free(m->tri);
    free(m);
}
Vertex3D CrossProduct(Vertex3D v1, Vertex3D v2)
{
    Vertex3D C;
    C.x = v1.y * v2.z - v1.z * v2.y;
    C.y = v1.z * v2.x - v1.x * v2.z;
    C.z = v1.x * v2.y - v1.y * v2.x;
    return C;
}

double Magnitude(Vertex3D v1)
{
    return sqrt(v1.x * v1.x + v1.y * v1.y + v1.z * v1.z);
}

double tri_area3D(Vertex3D v1, Vertex3D v2, Vertex3D v3)
{
    Vertex3D v12 = {v2.x - v1.x, v2.y - v1.y, v2.z - v1.z};
    Vertex3D v13 = {v3.x - v1.x, v3.y - v1.y, v3.z - v1.z};
    Vertex3D C = CrossProduct(v12,v13);
    return 0.5 * Magnitude(C);
}

Vertex3D NormalArea(Vertex3D v1, Vertex3D v2, Vertex3D v3)
{
    Vertex3D v12 = {v2.x - v1.x, v2.y - v1.y, v2.z - v1.z};
    Vertex3D v13 = {v3.x - v1.x, v3.y - v1.y, v3.z - v1.z};
    Vertex3D C = CrossProduct(v12,v13);
    C.x = C.x * 0.5;
    C.y = C.y * 0.5;
    C.z = C.z * 0.5;
    return C;
}

double Surface_Mesh3D(Mesh3D *m)
{
    double areaTot = 0.0;

    if(m->vert == NULL || m->tri == NULL){
        return 0.0;
    }
    for(int i=0; i<m->nt; i++){
        areaTot += tri_area3D(m->vert[m->tri[i].na], m->vert[m->tri[i].nb], m->vert[m->tri[i].nc]);
    }

    return areaTot;
}

double ScalarProduct(Vertex3D v1, Vertex3D v2)
{
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

Vertex3D Baricenter(Vertex3D v1, Vertex3D v2, Vertex3D v3)
{
    Vertex3D B;
    B.x = (v1.x + v2.x + v3.x)/3;
    B.y = (v1.y + v2.y + v3.y)/3;
    B.z = (v1.z + v2.z + v3.z)/3;
    return B;
}

double Volume_closed_Mesh3D(Mesh3D *m)
{
    double TotalFlux = 0.0;
    Vertex3D Normal;

    if(m->vert == NULL || m->tri == NULL){
        return 0.0;
    }
    for(int i=0; i<m->nt; i++){
        
        TotalFlux += ScalarProduct(Baricenter(m->vert[m->tri[i].na], m->vert[m->tri[i].nb], m->vert[m->tri[i].nc]), 
                                   NormalArea(m->vert[m->tri[i].na], m->vert[m->tri[i].nb], m->vert[m->tri[i].nc]));
    }

    return TotalFlux/3;
}