#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "mesh.h"
#include "mesh_io.h"
#include "mesh_adjacency.h"

#define NTRI_MAX_METHODE1 100000

// renvoie le temps ecoule en secondes entre deux appels a clock()
double secondes(clock_t debut, clock_t fin) {
    return (double)(fin - debut) / CLOCKS_PER_SEC;
}

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("usage : %s fichier.obj\n", argv[0]);
        return 1;
    }

    struct Mesh m;
    initialize_mesh(&m);
    if (read_mesh_from_wavefront_file(&m, argv[1]) != 0) {
        printf("impossible de lire %s\n", argv[1]);
        return 1;
    }
    printf("%s : %d sommets, %d triangles\n", argv[1], m.nvert, m.ntri);

    clock_t debut, fin;

    // methode 1
    if (m.ntri <= NTRI_MAX_METHODE1) {
        debut = clock();
        int *adj1 = build_adjacency_table1(&m);
        fin = clock();
        printf("methode 1 (naive)          : %.4f s\n", secondes(debut, fin));
        free(adj1);
    } else {
        printf("methode 1 (naive)          : ignoree (trop lente)\n");
    }

    // methode 2 (table de hash)
    debut = clock();
    int *adj2 = build_adjacency_table2(&m);
    fin = clock();
    printf("methode 2 (hash simple) : %.4f s\n", secondes(debut, fin));
    free(adj2);

    // methode 3 : (EdgeTable)
    debut = clock();
    int *adj3 = build_adjacency_table3(&m);
    fin = clock();
    printf("methode 3 (EdgeTable)      : %.4f s\n", secondes(debut, fin));
    free(adj3);

    // libere le maillage
    dispose_mesh(&m);
    return 0;
}
