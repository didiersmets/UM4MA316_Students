#include <stdio.h>
#include <stdlib.h>

//fixed capacity but size can vary (starting w/ 0)

struct Vertex{
    double x;
    double y;
    double z;
};

struct Triangle{
    int nA;
    int nB;
    int nC;
};

struct Mesh3D{
    int nv;
    int nt;
    int vtx_capacity;
    int tri_capacity;
    struct Triangle* tri;
    struct Vertex* vert;

};

void initialize_mesh3D(struct Mesh3D* m, int vtx_capacity, int tri_capacity);

void dispose_mesh3D(struct Mesh3D* m);

double volume_mesh3D(struct Mesh3D* m);


