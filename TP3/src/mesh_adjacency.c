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

void edge_table_initialize(struct EdgeTable *et, int nvert, int ntri) {
    et->head = malloc(sizeof(int) * nvert);
    et->next = malloc(sizeof(int) * ntri * 3);
    for (size_t i = 0 ; i < nvert ; i++) {
	et->head[i] = -1;
    }
    for (size_t i = 0 ; i < ntri * 3; i++) {
	et->next[i] = -1;
    }
    
}

void edge_table_dispose(struct EdgeTable *et) {
    free(et->head);
    free(et->next);
    free(et);
}

void edge_table_insert(int v1, int edge_code, struct EdgeTable *et) {
    int tmp = et->head[v1];
    if (tmp != -1) {
	head[v1] = edge_code; 
	et->next[edge_code] = tmp;
    }
    else {
	head[v1] = edge_code;
    }
}

int  edge_table_find(int v1, int v2, const struct EdgeTable *et, const struct Mesh *m) {
    int val = et->head[v1];
    size_t i = 0;
    while (next[val] != -1 && i < m->ntri) {
	if (m->triangles[val].v1 != v2) {
	    val = et->next[val];
	    i++;
	}
	else {
	    return val;
	}
    }
    return -1;
}

struct EdgeTable *build_edge_table3(const struct Mesh *m) {
    struct EdgeTable *et = malloc(sizeof(struct EdgeTable));
    edge_table_initialize(et, m->nvert, m->ntri);
    for (size_t i = 0 ; i < m->ntri ; i++) {
	struct Triangle t = m->triangles[i];
	int v1 = t.v1;
	int v2 = t.v2;
	
	int edge_code = 3 * i + edge_pos_in_tri(v1, v2, t);
	edge_table_insert(v1, edge_code, et); 
    }
    return et;
}

int *build_adjacency_table3(const struct Mesh *m) {
    int *adj = malloc(sizeof(int) * m->ntri * 3);
    struct EdgeTable *et = build_edge_table3(m);
    for (size_t i = 0 ; i < m->ntri ; i++) {
	struct Triangle t = m->triangles[i];
	
	for (size_t j = 0 ; j < 3 ; j++) {
	    int v1 = t.v[(j + 1) % 3];
	    int v2 = t.v[j];
	    int neighbour = edge_table_find(v2, v1, et, m);
	    adj[3 * i + j] = neighbour;
	}
    }

    return m;
}

