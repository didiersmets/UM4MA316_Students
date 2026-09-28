#include <stdio.h>
#include <stdlib.h>

//fixed capacity but size can vary (starting w/ 0)

struct Vertex{
    double x;
    double y;
};


struct Triangle{
    int nA;
    int nB;
    int nC;
};

struct Mesh2D{
    int nv;    
    int nt;
    struct Triangle* tri;
    struct Vertex* vert;

};

void initialize_mesh2D(struct Mesh2D* m, int vtx_capacity, int tri_capacity);

void dispose_mesh2D(struct Mesh2D* m);

double area_mesh2D(struct Mesh2D* m);


