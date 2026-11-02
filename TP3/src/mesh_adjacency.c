#include <stdlib.h>
#include "mesh.h"
#include "mesh_adjacency.h"


int edge_pos_in_tri(int v1, int v2, struct Triangle t) {

    if (v1 == t.v1) {
	return (v2 == t.v2)?0:-1;
    }
    else if (v1 == t.v2){
	return (v2 == t.v3)?1:-1;
    }
    else if (v1 == t.v3){
	return (v2 == t.v1)?2:-1;
    }
    return -1;
}

int tris_are_neighbors(int tri1, int tri2, const struct Mesh *m) {
    Triangle tri2 = m->triangles[tri2];
    Triangle tri1 = m->triangles[tri1];

    int pos = edge_pos_in_tri(tri2.v2, tri2.v1, tri1);

    if (pos == -1) {
	pos = edge_pos_in_tri(tri2.v3, tri2.v2, tri1);
	if (pos == -1) {
	    pos = edge_pos_in_tri(tri2.v1, tri2.v3, tri1);
	}
    }

    return pos;
}

int *build_adjacency_table1(const struct Mesh *m) {
    int *t = malloc(sizeof(int) * (m->ntri) * 3);
    for (size_t i = 0 ; i < 3 * m->ntri ; i++) {
	t[i] = -1;
    }
    int pos = -1;
    for (size_t i = 0 ; i < ntri ; i++) {
	Triangle tri1 = m->triangles[i];
	for (size_t j = 0 ; j < ntri ; j++) {
	    Triangle tri2 = m->triangles[j];
	    pos = tris_are_neighbors(tri1, tri2, m);
	    if (pos != -1) {
		t[i * 3 + pos] = tri2;
	    }
	}
    }
    return t;
}

struct HashTable *build_edge_table1(const struct Mesh *m) {
    HashTalbe *ht = hash_table_init(m->ntri * 3, sizeof(struct Edge), sizeof(int));
    struct Edge key;
    for (size_t i = 0 ; i < m->ntri ; i++) {
	key.v1 = m->triangles[i].v1; 
	key.v2 = m->triangles[i].v2;
	hash_table_insert(ht, &key, &i);

	key.v2 = m->triangles[i].v2; 
	key.v3 = m->triangles[i].v3;
	hash_table_insert(ht, &key, &i);
	
	key.v3 = m->triangles[i].v3; 
	key.v1 = m->triangles[i].v1;
	hash_table_insert(ht, &key, &i);
    }
    return ht;
}

int *build_adjacency_table2(const struct Mesh *m) {
    int *t = malloc(sizeof(int) * (m->ntri) * 3);
    for (size_t i = 0 ; i < 3 * m->ntri ; i++) {
	t[i] = -1;
    }
    HashTable *ht = build_edge_table1(m)
    int *neighbour;
    struct Edge key;
    for (size_t i = 0 ; i < ntri ; i++) {
	Triangle tri1 = m->triangles[i];
	key.v1 = tri1.v2;
	key.v2 = tri1.v1;

	neighbour = (int *)hash_table_find(ht, &key);
	if (neighbour) {
	    t[i * 3 + 0] = neighbour;
	}
	else {
	    t[i * 3 + 0] = -1;
	}

	Triangle tri1 = m->triangles[i];
	key.v1 = tri1.v3;
	key.v2 = tri1.v2;

	neighbour = (int *)hash_table_find(ht, &key);
	if (neighbour) {
	    t[i * 3 + 1] = neighbour;
	}
	else {
	    t[i * 3 + 1] = -1;
	}

	Triangle tri1 = m->triangles[i];
	key.v1 = tri1.v1;
	key.v2 = tri1.v3;

	neighbour = (int *)hash_table_find(ht, &key);
	if (neighbour) {
	    t[i * 3 + 2] = neighbour;
	}
	else {
	    t[i * 3 + 2] = -1;
	}
    }
    return t;
}

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

