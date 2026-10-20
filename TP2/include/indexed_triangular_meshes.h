#include <stddef.h>

struct Vertex {
    double x, y, z;

};
struct Triangle {
    int vertex[3];
};

struct Mesh2D {
    size_t nv;
    struct Vertex *vtx;
    size_t vtx_capacity;
    size_t nt;
    struct Triangle *tri;
    size_t tri_capacity;
};
    
int initialize_mesh2D(struct Mesh2D *m, size_t vtx_capacity, size_t tri_capacity);

// free mesh
void dispose_mesh2D(struct Mesh2D *m);

// calculate mesh area
double area_mesh2D(struct Mesh2D *m);

// reads a 2D mesh from a .mesh file and loads it into a Mesh2D
// the file shall be in the INRIA mesh format
int read_mesh2D(struct Mesh2D *m, const char *filename);

// writes the data of a Mesh2D data structure into a new file
// that can be sent directly to gnuplot for visualization
int mesh2D_to_gnuplot(struct Mesh2D *m, const char *filename);

// writes the data of a Mesh2D data structure into a new .mesh file
int write_mesh2D(struct Mesh2D *m, const char *filename);