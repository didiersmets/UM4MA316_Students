#include <stdio.h>
#include "../include/mesh_adjacency.h"

int edge_pos_in_tri(int v1, int v2, struct Triangle t) {

  if (v1 == t.v1 && v2 == t.v2) {
    return 0;
  }
  elseif (v1 == t.v2 && v2 == t.v3) {
    return 1;
  }
  elseif (v1 == t.v3 && v2 == t.v1) {
    return 2;
  }
  else {
    return -1;
  }
}

int tris_are_neighbors(int tri1, int tri2, const struct Mesh *m) {

  struct Triangle t2 = m->tri[tri2];
  struct Vertex vt2 = {t2.v1, t2.v2, t2.v3, t2.v1};

  for (int i=0; i<3; i++) {

    if(edge_pos_in_tri(vt2[i+1], vt2[i], m->tri[tri1]) != -1) {

      return edge_pos_in_tri(vt2[i+1], vt2[i], m->tri[tri1]);
    }
  }

  return edge_pos_in_tri(vt2[i+1], vt2[i], m->tri[tri1]);
}

int *build_adjacency_table1(const struct Mesh *m) {
  
  int *adj_array = malloc(sizeof(int) * 3 * m->ntri);

  for (int i=0; i<3*m->ntri; i++) {
    adj_array[i] = -1;
  }

  for (int i=0; i<m->ntri; i++) {
    for (int j=0; j<m->ntri; j++) {

      int pos = tris_are_neighbors(m->triangles[i], m->triangles[j], m);

      if (pos != -1) {
        adj_array[3*i+pos] = j;
      }
    }
  }

  return adj_array;
}

struct HashTable *build_edge_table1(const struct Mesh *m) {
  
}

