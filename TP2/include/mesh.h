#ifndef MESH
#define MESH

//models a point in 3D (marche aussi avec 2D si 
//                      on prend pas en compte z)

struct Vertex { 
  double x;
  double y;
  double z;
};

struct Triangle {
  int v1;
  int v2;
  int v3;
};

// marche pour mesh2D et mesh3D 

struct Mesh {
  int nv;
  struct Vertex *vert;
  int nt;
  struct Triangle *tri;
};

int initialize_mesh(struct Mesh *m, int vtx_capacity, int tri_capacity);

void dispose_mesh(struct Mesh *m);

double area_mesh2D(struct Mesh *m);

double volume_mesh3D(struct Mesh *m);

int read_mesh2D(struct Mesh *m, const char *filename);

int mesh2D_to_gnuplot(struct Mesh *m, const char *filename);

int write_mesh(struct Mesh *m, const char *filename);

#endif
