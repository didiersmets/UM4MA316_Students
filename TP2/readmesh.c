#include <stdio.h>
#include <stdlib.h>
#include "mesh2D.h"

// lit un fichier .mesh et remplit m:
int read_mesh2D(struct Mesh2D* m, const char* filename){

    m->nv = 0;
    m->nt = 0;
    m->vert = NULL;
    m->tri = NULL;

    //  1 parcourt le fichier pour compter les sommets et les triangles
    FILE * f = fopen(filename, "r");
    if (f == NULL) {
        return -1;
    }

    char line[256];

    int nv = 0;
    int nt = 0;

    while (fgets(line, 256, f)){
        if (sscanf(line, " Vertices %d", &nv) == 1){
            continue;
        }
        sscanf(line, " Triangles %d", &nt);
    }

    // sans sommets-triangles pas un maillage utilisable.
    if (nv <= 0 || nt <= 0) {
        fclose(f);
        return -1;
    }

    // reserver la memoire
    // en cas d'echec initialize_mesh2D a deja libere ce qu'elle avait reserve.
    if (initialize_mesh2D(m, nv, nt) != 0) {
        fclose(f);
        return -1;
    }

    // remplir
    // on ferme puis on rouvre pour reprendre la lecture au debut
    fclose(f);
    f = fopen(filename, "r");
    if (f == NULL) {
        dispose_mesh2D(m);
        return -1;
    }

    while (fgets(line, 256, f)){
        int n;

        if (sscanf(line, " Vertices %d", &n) == 1){

            // lire les vtx
            for (int i = 0; i < nv; i++) {
                double x, y; // z est ignoré
                if (fgets(line, 256, f) == NULL || sscanf(line, "%lf %lf", &x, &y) != 2) {
                    fclose(f);
                    dispose_mesh2D(m);
                    return -1;
                }
                m->vert[i].x = x;
                m->vert[i].y = y;
            }
            m->nv = nv;
        }
        else if (sscanf(line, " Triangles %d", &n) == 1){

            if (n != nt) {
                fclose(f);
                dispose_mesh2D(m);
                return -1;
            }

            // lire les triangles
            for (int i = 0; i < nt; i++) {
                int a, b, c;

                if (fgets(line, 256, f) == NULL || sscanf(line, "%d %d %d", &a, &b, &c) != 3) {
                    fclose(f);
                    dispose_mesh2D(m);
                    return -1;
                }
                // les indices vont de 1 a nv
                if (a < 1 || a > nv || b < 1 || b > nv
                    || c < 1 || c > nv) {
                    fclose(f);
                    dispose_mesh2D(m);
                    return -1;
                }
                // dans c : indices vont de 0 a nv - 1 : on enleve 1
                m->tri[i].idx[0] = a - 1;
                m->tri[i].idx[1] = b - 1;
                m->tri[i].idx[2] = c - 1;
            }
            m->nt = nt;
        }
    }

    fclose(f);
    return 0;
}


int mesh2D_to_gnuplot(struct Mesh2D* m, const char* filename){

    
    FILE * f = fopen(filename, "w");
    if (f == NULL) {
        return -1;
    }

    for (int i = 0 ; i<m->nt ; i++){
        struct Vertex a =m->vert[m->tri[i].idx[0]];
        struct Vertex b =m->vert[m->tri[i].idx[1]];
        struct Vertex c =m->vert[m->tri[i].idx[2]];

        fprintf(f, "%f %f \n", a.x , a.y);
        fprintf(f, "%f %f \n", b.x , b.y);
        fprintf(f, "%f %f \n", c.x , c.y);

    }

    fclose(f);

    return 0;

}


int write_mesh2D(struct Mesh2D* m, const char* filename){

    FILE * f = fopen(filename, "w");
    if (f == NULL) {
        return -1;
    }

    fprintf(f, "Vertices %d\n", m->nv);
    for (int i = 0 ; i<m->nv ; i++){ 
        fprintf(f, "%g %g \n", m->vert[i].x , m->vert[i].y);
    }

    fprintf(f, "Triangles %d\n", m->nt);
    for (int i = 0 ; i<m->nt ; i++){ 
        fprintf(f, "%d %d %d \n", m->tri[i].idx[0] + 1, m->tri[i].idx[1] +1 , m->tri[i].idx[2]);
    }

    fclose(f);
    return 0;

}