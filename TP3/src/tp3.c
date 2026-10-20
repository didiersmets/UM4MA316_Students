#include "mesh.h"
#include "mesh_io.h"
#include "mesh_adjacency.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

double wallclock_time()
{
	struct timeval tmp_time;
	gettimeofday(&tmp_time, NULL);
	return tmp_time.tv_sec + (tmp_time.tv_usec * 1.0e-6);
}

int main(int argc, char *argv[]) {


    if(argc < 2) {
        printf("usage: executable <meshFile.obj>\n");
        return 1;
    }

    struct Mesh *m = malloc(sizeof(struct Mesh));
    initialize_mesh(m);
    if(read_mesh_from_wavefront_file(m, argv[1]) == -1) {
        printf(".obj file does not exist\n");
        dispose_mesh(m);
        free(m);
        return 1;
    }

    int *adj;
    double start, end;

    // bugatti has more than 50000 ntri
    if(m -> ntri < 50000) {
        start = wallclock_time();
        adj = build_adjacency_table1(m);
        end = wallclock_time();
        printf("build_adjacency_table1 for %s: %.17g\n", argv[1], end - start);
        free(adj);
    }

    start = wallclock_time();
    adj = build_adjacency_table2(m);
    end = wallclock_time();
    printf("build_adjacency_table2 for %s: %.17g\n", argv[1], end - start);
    free(adj);

    start = wallclock_time();
    adj = build_adjacency_table3  (m);
    end = wallclock_time();
    printf("build_adjacency_table3 for %s: %.17g\n", argv[1], end - start);
    free(adj);

    dispose_mesh(m);
    free(m);

    return 0;
}