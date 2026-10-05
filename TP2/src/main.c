#include <stdio.h>
#include "../include/mesh.h"

int main() {
  
  struct Mesh m;
  initialize_mesh(&m, 3, 1);
  read_mesh2D(&m, "mesh2-tp2.mesh");
  printf("Vertices : %d\n", m.nv);
  for (int i=0; i<m.nv; i++) {
    printf("  %lf   %lf\n", m.vert[i].x, m.vert[i].y);
  }
  printf("Triangles : %d\n", m.nt);
  for (int i=0; i<m.nt; i++) {
    printf("  %d    %d    %d\n", m.tri[i].v1, m.tri[i].v2, m.tri[i].v3);
  }

  printf("Aire du mesh : %lf\n", area_mesh2D(&m));
  write_mesh(&m, "new_mesh.mesh");
  mesh2D_to_gnuplot(&m, "co_mesh.txt");
  dispose_mesh(&m);
  return 0;
}
