#include <stdio.h>
#include <stdlib.h>
#include "mesh2D.h"

int read_mesh2D(struct Mesh2D* m, const char* filename){

    FILE * f = fopen(filename, "r");
    char line[256];

    while (fgets(line, 256, f)){
        int nv;
        if (sscanf(line, " Vertices %d", &nv)==1){

            // reserver memoire
            m -> vert = malloc(nv * sizeof(struct Vertex));
            if (m ->vert == NULL) {
                break;
            }
            m->nv = nv;

            // lire les vtx



            for (int i =0; i < nv; i++) {
                fgets(line, 256, f);
                double x, y;
                sscanf(line, "%lf %lf", &x, &y);
                m->vert[i].x = x;
                m->vert[i].y = y;


            }

        }

    }

    fclose(f);
    return 0;

}

