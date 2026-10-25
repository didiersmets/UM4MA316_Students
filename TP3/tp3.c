#define _POSIX_C_SOURCE 199309L  

#include <stdlib.h>
#include <stdio.h>
#include <time.h>


#include "mesh_adjacency.h"
#include "mesh_io.h"
#include "mesh.h"

static double now(void)
{
	struct timespec ts;
	clock_gettime(CLOCK_MONOTONIC, &ts);
	return ts.tv_sec + 1e-9 * ts.tv_nsec;
}

int main(int argc, char *argv[])
{
	if (argc < 2) {
		fprintf(stderr, "usage: %s mesh.obj\n", argv[0]);
		return 1;
	}

	struct Mesh m;
	initialize_mesh(&m);
	if (read_mesh_from_wavefront_file(&m, argv[1]) != 0) {
		fprintf(stderr, "could not read %s\n", argv[1]);
		return 1;
	}
	printf("%s: %d vertices, %d triangles\n", argv[1], m.nvert, m.ntri);

	double t;
	int *adj;

	if (m.ntri <= 100000) {               // the O(ntri^2) method is too slow beyond this
		t = now();
		adj = build_adjacency_table1(&m);
		printf("method 1 (naive):      %.4f s\n", now() - t);
		free(adj);
	} else {
		printf("method 1 (naive):      skipped (mesh too large)\n");
	}

	t = now();
	adj = build_adjacency_table2(&m);
	printf("method 2 (hash table): %.4f s\n", now() - t);
	free(adj);

	t = now();
	adj = build_adjacency_table3(&m);
	printf("method 3 (edge table): %.4f s\n", now() - t);
	free(adj);

	dispose_mesh(&m);
	return 0;
}