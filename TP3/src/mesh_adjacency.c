#include "mesh_adjacency.h"

#include <stdio.h>
#include <stdlib.h>

// allocates an adjacency table of 3 * ntri integers filled with -1
static int *new_adjacency_table(int ntri)
{
	int *adj = malloc(3 * ntri * sizeof(int));
	if (adj == NULL) {
		printf("Error allocating the adjacency table\n");
		return NULL;
	}
	for (int i = 0; i < 3 * ntri; i++)
		adj[i] = -1;
	return adj;
}

/* Exercise 1 */
int edge_pos_in_tri(int v1, int v2, struct Triangle t)
{
	for (int i = 0; i < 3; i++) {
		if (t.idx[i] == v1 && t.idx[(i + 1) % 3] == v2)
			return i;
	}
	return -1;
}

/* Exercise 2 */
int tris_are_neighbors(int tri1, int tri2, const struct Mesh *m)
{
	struct Triangle t1 = m->triangles[tri1];
	struct Triangle t2 = m->triangles[tri2];

	// each edge a -> b of t2 is searched in t1 with opposite orientation
	for (int i = 0; i < 3; i++) {
		int pos = edge_pos_in_tri(t2.idx[(i + 1) % 3], t2.idx[i], t1);
		if (pos != -1)
			return pos;
	}
	return -1;
}

/* Exercise 3: O(ntri^2) */
int *build_adjacency_table1(const struct Mesh *m)
{
	int *adj = new_adjacency_table(m->ntri);
	if (adj == NULL)
		return NULL;

	for (int i = 0; i < m->ntri; i++) {
		for (int j = 0; j < m->ntri; j++) {
			if (i == j)
				continue;
			int pos = tris_are_neighbors(i, j, m);
			if (pos != -1)
				adj[3 * i + pos] = j;
		}
	}
	return adj;
}

/* Exercise 4: dictionary (v1, v2) -> index of the triangle containing v1 -> v2 */
struct HashTable *build_edge_table1(const struct Mesh *m)
{
	// capacity 2x the number of edges keeps the load factor below 1/2
	struct HashTable *ht =
		hash_table_init(2 * 3 * m->ntri, sizeof(struct Edge), sizeof(int));
	if (ht == NULL || ht->capacity == 0) {
		printf("Error allocating the edge hash table\n");
		if (ht)
			free(ht);
		return NULL;
	}

	for (int i = 0; i < m->ntri; i++) {
		for (int j = 0; j < 3; j++) {
			struct Edge e = { m->triangles[i].idx[j],
					  m->triangles[i].idx[(j + 1) % 3] };
			hash_table_insert(ht, &e, &i);
		}
	}
	return ht;
}

/* Exercise 5: O(ntri) on average, with the generic hash table */
int *build_adjacency_table2(const struct Mesh *m)
{
	int *adj = new_adjacency_table(m->ntri);
	if (adj == NULL)
		return NULL;

	struct HashTable *ht = build_edge_table1(m);
	if (ht == NULL) {
		free(adj);
		return NULL;
	}

	for (int i = 0; i < m->ntri; i++) {
		for (int j = 0; j < 3; j++) {
			// look for the opposite edge b -> a
			struct Edge e = { m->triangles[i].idx[(j + 1) % 3],
					  m->triangles[i].idx[j] };
			int *neighbor = hash_table_find(ht, &e);
			if (neighbor != NULL)
				adj[3 * i + j] = *neighbor;
		}
	}

	hash_table_fini(ht);
	free(ht);
	return adj;
}

/* Exercise 6: ad-hoc hash table with chaining, hash(v1, v2) = v1 */
void edge_table_initialize(struct EdgeTable *et, int nvert, int ntri)
{
	et->head = malloc(nvert * sizeof(int));
	et->next = malloc(3 * ntri * sizeof(int));
	if (et->head == NULL || et->next == NULL) {
		printf("Error allocating the edge table\n");
		edge_table_dispose(et);
		return;
	}
	for (int i = 0; i < nvert; i++)
		et->head[i] = -1;
	for (int i = 0; i < 3 * ntri; i++)
		et->next[i] = -1;
}

void edge_table_dispose(struct EdgeTable *et)
{
	free(et->head);
	free(et->next);
	et->head = NULL;
	et->next = NULL;
}

// edge_code = 3 * i + j is the edge number j of the triangle i
void edge_table_insert(int v1, int edge_code, struct EdgeTable *et)
{
	et->next[edge_code] = et->head[v1];
	et->head[v1] = edge_code;
}

// returns the code of the edge v1 -> v2, or -1 if it is not in the mesh
int edge_table_find(int v1, int v2, const struct EdgeTable *et,
		    const struct Mesh *m)
{
	for (int code = et->head[v1]; code != -1; code = et->next[code]) {
		int i = code / 3;
		int j = code % 3;
		if (m->triangles[i].idx[(j + 1) % 3] == v2)
			return code;
	}
	return -1;
}

struct EdgeTable *build_edge_table3(const struct Mesh *m)
{
	struct EdgeTable *et = malloc(sizeof(struct EdgeTable));
	if (et == NULL)
		return NULL;
	edge_table_initialize(et, m->nvert, m->ntri);
	if (et->head == NULL) {
		free(et);
		return NULL;
	}

	for (int i = 0; i < m->ntri; i++) {
		for (int j = 0; j < 3; j++)
			edge_table_insert(m->triangles[i].idx[j], 3 * i + j, et);
	}
	return et;
}

int *build_adjacency_table3(const struct Mesh *m)
{
	int *adj = new_adjacency_table(m->ntri);
	if (adj == NULL)
		return NULL;

	struct EdgeTable *et = build_edge_table3(m);
	if (et == NULL) {
		free(adj);
		return NULL;
	}

	for (int i = 0; i < m->ntri; i++) {
		for (int j = 0; j < 3; j++) {
			int code = edge_table_find(m->triangles[i].idx[(j + 1) % 3],
						   m->triangles[i].idx[j], et, m);
			if (code != -1)
				adj[3 * i + j] = code / 3;
		}
	}

	edge_table_dispose(et);
	free(et);
	return adj;
}
