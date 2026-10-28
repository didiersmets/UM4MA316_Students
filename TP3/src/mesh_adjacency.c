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
