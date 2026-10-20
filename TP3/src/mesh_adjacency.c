#include <stdio.h>
#include <stdlib.h>

#include "mesh_adjacency.h"

int edge_pos_in_tri(int v1, int v2, struct Triangle t){
    for(int i = 0; i < 3; i++){
        if(t.idx[i] == v1 && t.idx[(i+1)%3]== v2) return i; 
    }
    return -1;
}

int tris_are_neighbors(int tri1, int tri2, const struct Mesh *m){
    for(int v = 0; v < 3; v++){
        int v1 = m->triangles[tri1].idx[v];
        int v2 = m->triangles[tri1].idx[(v+1)%3];

        if(edge_pos_in_tri(v2,v1,m->triangles[tri2]) != -1) return v;
    }
    return -1;
}

int *build_adjacency_table1(const struct Mesh *m){
    int size = 3 * m->ntri;
    int *adj = malloc(size * sizeof(int));
    if(adj == NULL) return NULL;

    for(int i = 0; i < size; i++){
        adj[i] = -1;
    }

    int ntri = m->ntri;
    for(int j = 0; j < ntri; j++){
        for(int k = 0; k < ntri; k++){
            if(j == k) continue;

            int edge = tris_are_neighbors(j,k,m);
            if(edge != -1){
                adj[3*j+edge] = k;
            }
        }
    }
    return adj;
}

struct HashTable *build_edge_table1(const struct Mesh *m){
    struct HashTable *tbl = hash_table_init(2 * 3 * m->ntri, sizeof(struct Edge), sizeof(int));
    if(tbl == NULL) return NULL;

    for(int i = 0; i < m->ntri; i++){
        for(int j = 0; j < 3; j++){
            struct Edge e;
            e.v1 = m->triangles[i].idx[j];
            e.v2 = m->triangles[i].idx[(j+1)%3];
            hash_table_insert(tbl, &e, &i);
        }
    }
    return tbl;
}

int *build_adjacency_table2(const struct Mesh *m){

    struct HashTable *edge_table = build_edge_table1(m); 
    if(edge_table == NULL) return NULL;

    int size = 3 * m->ntri;
    int *adj = malloc(size * sizeof(int));
    if(adj == NULL){
        hash_table_fini(edge_table);
        free(edge_table);
        return NULL;
    }

    for(int i = 0; i < size; i++){
        adj[i] = -1;
    }

    for(int i = 0; i < m->ntri; i++){
        for(int j = 0; j < 3; j++){
            struct Edge e;
            e.v2 = m->triangles[i].idx[j];
            e.v1 = m->triangles[i].idx[(j+1)%3];

            int *val = hash_table_find(edge_table,&e);

            if(val != NULL){
                adj[3*i+j] = *val;
            }
        }
    }

    hash_table_fini(edge_table);
    free(edge_table);
    return adj;
}

void edge_table_initialize(struct EdgeTable *et, int nvert, int ntri){
    et->head = malloc(nvert*sizeof(int));
    et->next = malloc(3*ntri*sizeof(int));

    if(et->head == NULL || et->next == NULL){
        free(et->head);
        free(et->next);
        et->head = NULL;
        et->next = NULL;
    }

    for(int i = 0; i < nvert; i++){
        et->head[i] = -1;
    }
}

void edge_table_dispose(struct EdgeTable *et){
    free(et->head);
    free(et->next);
    et->head = NULL;
    et->next = NULL;
}

void edge_table_insert(int v1, int edge_code, struct EdgeTable *et){
    et->next[edge_code] = et->head[v1];
    et->head[v1] = edge_code;
}

int edge_table_find(int v1, int v2, const struct EdgeTable *et, const struct Mesh *m){
    for(int c = et->head[v1]; c != -1; c = et->next[c]){
        int i = c / 3;
        int j = c % 3;
        if(m->triangles[i].idx[(j+1)%3] == v2) return c;
    }
    return -1;
}

struct EdgeTable *build_edge_table3(const struct Mesh *m){
    struct EdgeTable *et = malloc(sizeof(struct EdgeTable));
    if(et == NULL) return NULL;

    edge_table_initialize(et,m->nvert,m->ntri);
    if(et->head == NULL){
        free(et);
        return NULL;
    }

    for(int i = 0; i < m->ntri; i++){
        for(int j = 0; j < 3; j++){
            int v1 = m->triangles[i].idx[j];
            edge_table_insert(v1,3*i+j,et);
        }
    }

    return et;
}

int *build_adjacency_table3(const struct Mesh *m){
    struct EdgeTable *et = build_edge_table3(m);
    if(et == NULL) return NULL;

    int size = 3 * m->ntri;
    int *adj = malloc(size * sizeof(int));
    if(adj == NULL){
        edge_table_dispose(et);
        free(et);
        return NULL;
    }   

    for(int i = 0; i < m->ntri; i++){
        for(int j = 0; j < 3; j++){
            int v1 = m->triangles[i].idx[j];
            int v2 = m->triangles[i].idx[(j+1)%3];

            int edge_code = edge_table_find(v2,v1,et,m);

            if(edge_code != -1){
                adj[3*i+j] = edge_code / 3;
            }else{
                adj[3*i+j] = -1;
            }
        }
    }

    edge_table_dispose(et);
    free(et);
    return adj;
}
