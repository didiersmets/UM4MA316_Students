#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "mesh.h"
#include "mesh_adjacency.h"
#include "mesh_io.h"

// above this number of triangles the O(ntri^2) method is skipped
#define MAX_TRI_NAIVE 50000

static double now(void)
{
	struct timespec ts;
	clock_gettime(CLOCK_MONOTONIC, &ts);
	return ts.tv_sec + ts.tv_nsec * 1e-9;
}

int main(int argc, char *argv[])
{
	if (argc < 2) {
		printf("Usage: %s <mesh.obj>\n", argv[0]);
		return 1;
	}

	struct Mesh m;
	initialize_mesh(&m);
	if (read_mesh_from_wavefront_file(&m, argv[1]) != 0) {
		printf("Cannot read %s\n", argv[1]);
		return 1;
	}
	printf("%s: %d vertices, %d triangles\n", argv[1], m.nvert, m.ntri);

	double t;
	int *adj;

	if (m.ntri <= MAX_TRI_NAIVE) {
		t = now();
		adj = build_adjacency_table1(&m);
		printf("build_adjacency_table1 (naive):      %10.6f s\n", now() - t);
		free(adj);
	} else {
		printf("build_adjacency_table1 (naive):      skipped (too many triangles)\n");
	}

	t = now();
	adj = build_adjacency_table2(&m);
	printf("build_adjacency_table2 (hash table): %10.6f s\n", now() - t);
	free(adj);

	t = now();
	adj = build_adjacency_table3(&m);
	printf("build_adjacency_table3 (edge table): %10.6f s\n", now() - t);
	free(adj);

	dispose_mesh(&m);
	return 0;
}
