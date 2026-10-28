
#include "mesh_io.h"

#include <stdio.h>   // Used for fopen, fclose, fgets, sscanf and printf
#include <stdlib.h>  // Used for malloc and free
#include <string.h>  // Used for strcmp

#include "mesh.h"
#include "hash_tables.h"
#include "mesh_adjacency.h"



int edge_pos_in_tri(int v1, int v2, struct Triangle t){
    if (t.v1==v1 && t.v2==v2){return 0;}
    if (t.v2==v1 && t.v3==v2){return 1;}
    if (t.v3==v1 && t.v1==v2){return 2;}
    return -1;
}

int tris_are_neighbors(int tri1, int tri2, const struct Mesh *m){
    int i;
    int j;
    struct Triangle t1 = m->triangles[tri1];
    struct Triangle t2 = m->triangles[tri2];

    if (edge_pos_in_tri(t1.v2, t1.v1, t2) != -1){return 0;}
    if (edge_pos_in_tri(t1.v3, t1.v2, t2) != -1){return 1;}
    if (edge_pos_in_tri(t1.v1, t1.v3, t2) != -1){return 2;}

    return -1;
}

int *build_adjacency_table1(const struct Mesh *m){
    int *adj = malloc(sizeof(int)*(3 * m->ntri));
    for (int i = 0; i < 3*(m->ntri); i++){ adj[i] = -1;}

    for (int t1 = 0; t1 < m->ntri; t1++){
        for (int t2 = 0; t2 < m->ntri; t2++){
            int res = tris_are_neighbors(t1, t2, m);
            if(res != -1){
                adj[3*t1 + res] = t2;
            } 
        }
    }
    return adj;
}

struct HashTable *build_edge_table1(const struct Mesh *m){
    struct HashTable *hash = hash_table_init(3*(m->ntri), sizeof(struct Edge), sizeof(int));

    for (int tri = 0; tri < m->ntri; tri++){
        struct Edge key1;
        key1.v1 = m->triangles[tri].v1;
        key1.v2 = m->triangles[tri].v2;
        hash_table_insert(hash, &key1, &tri);

        struct Edge key2;
        key2.v1 = m->triangles[tri].v2;
        key2.v2 = m->triangles[tri].v3;
        hash_table_insert(hash, &key2, &tri);

        struct Edge key3;
        key3.v1 = m->triangles[tri].v3;
        key3.v2 = m->triangles[tri].v1;
        hash_table_insert(hash, &key3, &tri);
    }

    return hash;
}

int *build_adjacency_table2(const struct Mesh *m){
    int *adj = malloc(sizeof(int)*(3 * m->ntri));
    for (int i = 0; i < 3*(m->ntri); i++){ adj[i] = -1;}

    struct HashTable *hash = build_edge_table1(m);

    for (int tri = 0; tri < m->ntri; tri++){
            struct Triangle t = m->triangles[tri];
            struct Edge key;
            int *voi;

            key.v1 = t.v2;
            key.v2 = t.v1;
            voi = hash_table_find(hash, &key);
            if (voi != NULL){adj[3*tri] = *voi;}

            key.v1 = t.v3;
            key.v2 = t.v2;
            voi = hash_table_find(hash, &key);
            if (voi != NULL){adj[3*tri+1] = *voi;}

            key.v1 = t.v1;
            key.v2 = t.v3;
            voi = hash_table_find(hash, &key);
            if (voi != NULL){adj[3*tri+2] = *voi;}
        }

    hash_table_fini(hash);
    free(hash);

    return adj;
}

void edge_table_initialize(struct EdgeTable *et, int nvert, int ntri){
    et->head = malloc(nvert*sizeof(int));
    et->next = malloc(3*ntri*sizeof(int));
    for (int i = 0; i < nvert; i++){
        et->head[i] = -1;
    }
    for (int i = 0; i < 3 * ntri; i++){
        et->next[i] = -1;
    }
}

void edge_table_dispose(struct EdgeTable *et){
    free(et->head);
    free(et->next);
}

void edge_table_insert(int v1, int edge, struct EdgeTable *et){
    int tmp = et->head[v1];
    et->head[v1] = edge;
    et->next[edge] = tmp;
}

int edge_table_find(int v1, int v2, const struct EdgeTable *et, const struct Mesh *m){
    int h = et->head[v1];
    while (h != -1){
        int tri = h/3;
        int pos = h%3;
        struct Triangle t = m->triangles[tri];

        if ((pos == 0 && t.v2 == v2) || (pos == 1 && t.v3 == v2) || (pos == 2 && t.v1 == v2)){
            return tri;
        }
        h = et->next[h];
    }

    return -1;
}

struct EdgeTable *build_edge_table3(const struct Mesh *m){
    struct EdgeTable *et = malloc(sizeof(struct EdgeTable));
    edge_table_initialize(et, m->nvert, m->ntri);

    for (int tri = 0; tri < m->ntri; tri++){
        struct Triangle t = m->triangles[tri];
        edge_table_insert(t.v1, 3*tri, et);
        edge_table_insert(t.v2, 3*tri+1, et);
        edge_table_insert(t.v3, 3*tri+2, et);
    }

    return et;
}

int *build_adjacency_table3(const struct Mesh *m){
    int *adj = malloc(3 * m->ntri * sizeof(int));

    for (int i = 0; i < 3 * m->ntri; i++){adj[i] = -1;}

    struct EdgeTable *et = build_edge_table3(m);

    for (int tri = 0; tri < m->ntri; tri++){
        struct Triangle t = m->triangles[tri];

        adj[3*tri] = edge_table_find(t.v2, t.v1, et, m);
        adj[3*tri + 1] = edge_table_find(t.v3, t.v2, et, m);
        adj[3*tri + 2] = edge_table_find(t.v1, t.v3, et, m);
    }

    edge_table_dispose(et);
    free(et);

    return adj;
}