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
