#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "../include/mesh_adjacency.h"
#include "../include/hash_tables.h"

int edge_pos_in_tri(int v1, int v2, struct Triangle t) {

  if (v1 == t.v1 && v2 == t.v2) {
    return 0;
  }
  else if (v1 == t.v2 && v2 == t.v3) {
    return 1;
  }
  else if (v1 == t.v3 && v2 == t.v1) {
    return 2;
  }
  else {
    return -1;
  }
}

int tris_are_neighbors(int tri1, int tri2, const struct Mesh *m) {

  struct Triangle t2 = m->triangles[tri2];
  int vt2[] = {t2.v1, t2.v2, t2.v3, t2.v1};

  for (int i=0; i<3; i++) {

    if(edge_pos_in_tri(vt2[i+1], vt2[i], m->triangles[tri1]) != -1) {

      return edge_pos_in_tri(vt2[i+1], vt2[i], m->triangles[tri1]);
    }
  }

  return -1;
}

// pas oublier de free après utilisation de la fonction

int *build_adjacency_table1(const struct Mesh *m) {
  
  int *adj_array = malloc(sizeof(int) * 3 * m->ntri);

  for (int i=0; i<3*m->ntri; i++) {
    adj_array[i] = -1;
  }

  for (int i=0; i<m->ntri; i++) {
    for (int j=0; j<m->ntri; j++) {
      
      if (i != j) {

        int pos = tris_are_neighbors(i, j, m);

        if (pos != -1) {
          adj_array[3*i+pos] = j;
        }
      }
    }
  }

  return adj_array;
}

struct HashTable *build_edge_table1(const struct Mesh *m) {
  
  unsigned capacity = 3 * m->ntri;
  unsigned kl = sizeof(struct Edge);
  unsigned vl = sizeof(int);
  struct HashTable *ht = hash_table_init(capacity, kl, vl);
  
  for (int i=0; i<m->ntri; i++) {

    struct Triangle i_tri = m->triangles[i];

    struct Edge first_edge;
    first_edge.v1 = i_tri.v1;
    first_edge.v2 = i_tri.v2;
    hash_table_insert(ht, &first_edge, &i);
    
    struct Edge second_edge;
    second_edge.v1 = i_tri.v2;
    second_edge.v2 = i_tri.v3;
    hash_table_insert(ht, &second_edge, &i);
    
    struct Edge third_edge;
    third_edge.v1 = i_tri.v3;
    third_edge.v2 = i_tri.v1;
    hash_table_insert(ht, &third_edge, &i);
  }

  return ht;
}

// pas oublier de free après utilisation de la fonction

int *build_adjacency_table2(const struct Mesh *m) {
  
  struct HashTable *edge_table = build_edge_table1(m);

  int *adj_array = malloc(3 * m->ntri * sizeof(int));

  for (int i=0; i<m->ntri; i++) {
    
    struct Triangle i_tri = m->triangles[i];
    int vt[] = {i_tri.v1, i_tri.v2, i_tri.v3, i_tri.v1};

    for (int j=0; j<3; j++) {

      struct Edge reversed_edge;
      reversed_edge.v1 = vt[j+1];
      reversed_edge.v2 = vt[j];

      int *neighbor = hash_table_find(edge_table, &reversed_edge);

      adj_array[3*i+j] = (neighbor != NULL) ? *neighbor : -1;
    }
  }
  
  hash_table_fini(edge_table);
  free(edge_table);
  return adj_array;
}

void edge_table_initialize(struct EdgeTable *et, int nvert, int ntri) {
  
  et->head = malloc(nvert * sizeof(int));
  for (int i=0; i<nvert; i++) {
    et->head[i] = -1;
  }

  et->next = malloc(3 * ntri * sizeof(int));
  for (int i=0; i<3*ntri; i++) {
    et->next[i] = -1;
  }

  return;
}

void edge_table_dispose(struct EdgeTable *et) {
  
  free(et->head);
  free(et->next);

  return;
}

void edge_table_insert(int v1, int edge_code, struct EdgeTable *et) {
  
  if (et->head[v1] == -1) {
    et->head[v1] = edge_code;
    return;
  }
  else {
    int tmp = et->head[v1];
    et->head[v1] = edge_code;
    et->next[edge_code] = tmp;
    return;
  }
}

int  edge_table_find(int v1, int v2, const struct EdgeTable *et, 
                     const struct Mesh *m) {

  int res = et->head[v1];

  while (res != -1) {

    int i = res / 3;
    int j = res % 3;

    struct Triangle i_tri = m->triangles[i];
    int vt[] = {i_tri.v1, i_tri.v2, i_tri.v3, i_tri.v1};

    if (vt[j] == v1 && vt[j+1] == v2) {
      return i;
    }
    else {
      res = et->next[res];
    }
  }
  
  return -1;
}

struct EdgeTable *build_edge_table3(const struct Mesh *m) {

  struct EdgeTable *et = malloc(sizeof(struct EdgeTable));
  edge_table_initialize(et, m->nvert, m->ntri);

  for (int i=0; i<m->ntri; i++) {

    struct Triangle i_tri = m->triangles[i];
    int vt[] = {i_tri.v1, i_tri.v2, i_tri.v3};

    for (int j=0; j<3; j++) {

      int edge_code = 3*i+j;
      edge_table_insert(vt[j], edge_code, et);
    }
  }

  return et;
}

// pas oublier de free après utilisation de la fonction

int *build_adjacency_table3(const struct Mesh *m) {

  struct EdgeTable *et = build_edge_table3(m);
  int *adj_array = malloc(3 * m->ntri * sizeof(int));

  for (int i=0; i<m->ntri; i++) {

    struct Triangle i_tri = m->triangles[i];
    int vt[] = {i_tri.v1, i_tri.v2, i_tri.v3, i_tri.v1};
 
    for(int j=0; j<3; j++) {
      
      adj_array[3*i+j] = edge_table_find(vt[j+1], vt[j], et, m);
    }
  }
  
  edge_table_dispose(et);
  free(et);
  return adj_array;
}

