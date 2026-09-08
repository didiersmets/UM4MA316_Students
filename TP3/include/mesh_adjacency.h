#ifndef _MESH_ADJACENCY_H
#define _MESH_ADJACENCY_H

#include "mesh.h"
#include "hash_tables.h"

struct Edge {
	int v1;
	int v2;
};

int edge_pos_in_tri(int v1, int v2, struct Triangle t);

int tris_are_neighbors(int tri1, int tri2, const struct Mesh *m);

int *build_adjacency_table1(const struct Mesh *m);

struct HashTable *build_edge_table1(const struct Mesh *m);

int *build_adjacency_table2(const struct Mesh *m);

struct HashTable *build_edge_table2(const struct Mesh *m);

struct EdgeTable {
	int *head;
	int *next;
};

void edge_table_initialize(struct EdgeTable *et, int nvert, int ntri);

void edge_table_dispose(struct EdgeTable *et);

void edge_table_insert(int v1, int edge_code, struct EdgeTable *et);

int  edge_table_find(int v1, int v2, const struct EdgeTable *et, 
                                                const struct Mesh *m);

struct EdgeTable *build_edge_table3(const struct Mesh *m);

int *build_adjacency_table3(const struct Mesh *m);

#endif
