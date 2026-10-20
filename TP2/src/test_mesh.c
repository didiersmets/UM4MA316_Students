#include "../include/indexed_triangular_meshes.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

    struct Mesh2D *m = malloc(sizeof(struct Mesh2D));

    char line[256];

    printf("\noriginal mesh file:\n\n");
    FILE *f = fopen("mesh2-tp2.mesh", "r");
    if(f == NULL) {
        printf("Error opening the file\n");
        return 1;
    }
    while(fgets(line, sizeof(line), f) != NULL) printf("%s", line);

    if(read_mesh2D(m, "mesh2-tp2.mesh")) {
        return 1;
    }

    fclose(f);fclose(f);

    printf("\nmesh built from file:\n\n");

    printf("vertices: %zu\n", m -> nv);
    for(int i = 0; i < m -> nv; i++) {
        printf("\t%.17g\t%.17g\t%.17g\n", m -> vtx[i].x, m -> vtx[i].y, m -> vtx[i].z);
    }

    printf("triangles: %zu\n", m -> nt);
    for(int i = 0; i < m -> nt; i++) {
        printf("\t%d\t%d\t%d\n", m -> tri[i].vertex[0], m -> tri[i].vertex[1], m -> tri[i].vertex[2]);
    }

    if(write_mesh2D(m, "output_mesh.mesh")) {
        return 1;
    }

    printf("\nmesh file:\n\n");

    f = fopen("output_mesh.mesh", "r");
    if(f == NULL) {
        printf("error opening the file\n");
    }
    while(fgets(line, sizeof(line), f) != NULL)   printf("%s", line);

    if(mesh2D_to_gnuplot(m, "mesh.dat")) {
        return 1;
    }

    fclose(f);
    dispose_mesh2D(m);

    return 0;
}