#include <stdio.h>
#include "mesh2D.h"

int main(void) {

    struct Mesh2D m;

    if (initialize_mesh2D(&m, 4, 2) != 0){
        printf("Erreur : mempire insuffisante\n");
        return 1;
    }

    m.nv =4;
    m.vert[0].x = 0.0;  m.vert[0].y = 0.0;
    m.vert[1].x = 1.0;  m.vert[1].y = 0.0;
    m.vert[2].x = 1.0;  m.vert[2].y = 1.0;
    m.vert[3].x = 0.0;  m.vert[3].y = 1.0;

    m.nt = 2;
    m.tri[0].idx[0] = 0;  m.tri[0].idx[1] = 1;  m.tri[0].idx[2] = 2;
    m.tri[1].idx[0] = 0;  m.tri[1].idx[1] = 2;  m.tri[1].idx[2] = 3;

    printf("Aire du carre : %f (attendu : 1.000000)\n", area_mesh2D(&m));

    // sens inverse,
    m.tri[0].idx[1] = 2;  m.tri[0].idx[2] = 1;
    m.tri[1].idx[1] = 3;  m.tri[1].idx[2] = 2;

    printf("Aire inversee : %f (attendu : -1.000000)\n", area_mesh2D(&m));


    dispose_mesh2D(&m);
    return 0;

}