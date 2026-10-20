#include "mesh_adjacency.h"

#include <stdio.h>
#include <stdlib.h>

int edge_pos_in_tri(int v1, int v2, struct Triangle t) {
    for(int i = 0; i < 3; i++) {
        if(t.idx[i] == v1 && t.idx[(i + 1) % 3] == v2) {
            return i;
        }
    }
    return -1;
}

int tris_are_neighbors(int tri1, int tri2, const struct Mesh *m) {

    struct Triangle triangle1 = m -> triangles[tri1];
    struct Triangle triangle2 = m -> triangles[tri2];
    int pos;

    for(int i = 0; i < 3; i++) {
        pos = edge_pos_in_tri(triangle2.idx[(i + 1) % 3], triangle2.idx[i], triangle1);
        if(pos != -1)
            return pos;
    }

    return pos;
}

int *build_adjacency_table1(const struct Mesh *m) {

    int *adj = malloc(m->ntri * 3 * sizeof(int));
    if(adj == NULL) {
        printf("error allocating adjacency table\n");
        return NULL;
    }
    int pos;

    for(int i = 0; i < m->ntri * 3; i++) {
        adj[i] = -1;
    }

    for(int i = 0; i < m -> ntri; i++) {
        for(int j = 0; j < m -> ntri; j++) {
            if(i == j) continue;

            pos = tris_are_neighbors(i, j, m);
            if(pos != -1)
                adj[i * 3 + pos] = j;
        }
    }

    return adj;
}

struct HashTable *build_edge_table1(const struct Mesh *m) {

    struct HashTable *ht = hash_table_init(m->ntri * 3 * 2, sizeof(struct Edge), sizeof(int));

    struct Edge *edge = malloc(sizeof(struct Edge));

    for(int i = 0; i < m -> ntri; i++) {
        for(int j = 0; j < 3; j++) {
            edge -> v1 = m -> triangles[i].idx[j];
            edge -> v2 = m -> triangles[i].idx[(j + 1) % 3];
            hash_table_insert(ht, edge, &i);
        }
    }

    free(edge);

    return ht;
}

int *build_adjacency_table2(const struct Mesh *m) {

    int *adj = malloc(m -> ntri * 3 * sizeof(int));
    if(adj == NULL) {
        printf("error allocating adjacency table\n");
        return NULL;
    }

    struct HashTable *ht = build_edge_table1(m);
    struct Edge *edge = malloc(sizeof(struct Edge));
    void *adj_triangle;

    for(int i = 0; i < m -> ntri; i++) {
        for(int j = 0; j < 3; j++) {
            edge -> v1 = m -> triangles[i].idx[(j + 1) % 3];
            edge -> v2 = m -> triangles[i].idx[j];
            adj_triangle = hash_table_find(ht, edge);
            adj[i * 3 + j] = adj_triangle == NULL ? -1 : *(int*)adj_triangle;
        }
    }

    free(edge);
    hash_table_fini(ht);
    free(ht);

    return adj;
}

void edge_table_initialize(struct EdgeTable *et, int nvert, int ntri) {

    et -> head = malloc(nvert * sizeof(int));
    if(et -> head == NULL) {
        printf("error allocation the head array in the edge table\n");
        return;
    }
    for(int i = 0; i < nvert; i++) {
        et -> head[i] = -1;
    }

    et -> next = malloc(ntri * 3 * sizeof(int));
    if(et -> next == NULL) {
        printf("error allocation the next array in the edge table\n");
        return;
    }
    for(int i = 0; i < ntri * 3; i++) {
        et -> next[i] = -1;
    }
}

void edge_table_dispose(struct EdgeTable *et) {
    free(et -> head);
    free(et -> next);
}

void edge_table_insert(int v1, int edge_code, struct EdgeTable *et) {

    if(et -> head[v1] == -1)  {
        et -> head[v1] = edge_code;

    } else {
        int tmp = et -> head[v1];
        et -> head[v1] = edge_code;
        et -> next[edge_code] = tmp;
    }
}

int edge_table_find(int v1, int v2, const struct EdgeTable *et, const struct Mesh *m) {
    int code = et->head[v1];

    while (code != -1) {
        int i = code / 3;
        int j = code % 3;
        int successor = m->triangles[i].idx[(j + 1) % 3];

        if (successor == v2)
            return code;

        code = et->next[code];
    }

    return -1;
}

struct EdgeTable *build_edge_table3(const struct Mesh *m) {

    struct EdgeTable *et = malloc(sizeof(struct EdgeTable));
    edge_table_initialize(et, m -> nvert, m -> ntri);

    for(int i = 0; i < m -> ntri; i++) {
        for(int j = 0; j < 3; j++) {
            edge_table_insert(m -> triangles[i].idx[j], i * 3 + j, et);
        }
    }

    return et;
}

int *build_adjacency_table3(const struct Mesh *m) {

    int *adj = malloc(m -> ntri * 3 * sizeof(int));
    if(adj == NULL) {
        printf("error allocating the adjacent table\n");
        return NULL;
    }

    for(int i = 0; i < m -> ntri * 3; i++) {
        adj[i] = -1;
    }
    
    struct EdgeTable *et = build_edge_table3(m);
    int code;
    int adj_triangle;

    for(int i = 0; i < m -> ntri; i++) {
        for(int j = 0; j < 3; j++) {
            code = edge_table_find(m -> triangles[i].idx[(j + 1) % 3], 
                                        m -> triangles[i].idx[j], et, m);
            if(code == -1) continue;
            adj_triangle = code / 3;
            adj[i * 3 + j] = adj_triangle;
        }
    }

    edge_table_dispose(et);
    free(et);

    return adj;
}