#include <stdio.h>
#include "es1.h"
#include "es2.h"

// usage: ./test_mesh file.mesh
// reads the mesh, prints its area, writes it back (.mesh) and exports it
// for gnuplot, then re-reads the written file and checks it is identical
int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s file.mesh\n", argv[0]);
        return 1;
    }

    Mesh2D m;
    if (read_mesh2D(&m, argv[1]))
        return 1;
    printf("%s: %d vertices, %d triangles, area = %.10f\n", argv[1], m.nv, m.nt,
           area_mesh2D(&m));

    if (write_mesh2D(&m, "output.mesh") || mesh2D_to_gnuplot(&m, "mesh.dat")) {
        dispose_mesh2D(&m);
        return 1;
    }
    printf("written output.mesh and mesh.dat (gnuplot: plot \"mesh.dat\" w l)\n");

    Mesh2D copy;
    if (read_mesh2D(&copy, "output.mesh")) {
        dispose_mesh2D(&m);
        return 1;
    }
    int same = copy.nv == m.nv && copy.nt == m.nt;
    for (int i = 0; same && i < m.nv; i++)
        same = copy.vtx[i].x == m.vtx[i].x && copy.vtx[i].y == m.vtx[i].y;
    for (int i = 0; same && i < m.nt; i++)
        same = copy.tri[i].a == m.tri[i].a && copy.tri[i].b == m.tri[i].b &&
               copy.tri[i].c == m.tri[i].c;
    printf("round trip write/read: %s\n", same ? "OK" : "MISMATCH");

    dispose_mesh2D(&copy);
    dispose_mesh2D(&m);
    return same ? 0 : 1;
}
