#include "exercices.h"
#include <math.h>

int edge_pos_in_tri(int v1, int v2, struct Triangle t){
    if (t.iA == v1 && t.iB == v2) {
        return 0;
    }

    if (t.iB == v1 && t.iC == v2) {
        return 1;
    }

    if (t.iC == v1 && t.iA == v2) {
        return 2;
    }

    return -1;
}

int tris_are_neighbors(int tri1, int tri2, const struct Mesh *m){
    struct Triangle t1 = m->tri[tri1];
    struct Triangle t2 = m->tri[tri2];

    int edges_t1[3][2] = {
        {t1.iA, t1.iB}, // Edge 0
        {t1.iB, t1.iC}, // Edge 1
        {t1.iC, t1.iA}  // Edge 2
    };

    for (int i = 0; i < 3; ++i) {
        int u = edges_t1[i][0];
        int v = edges_t1[i][1];
        
        if (edge_pos_in_tri(v, u, t2) != -1) {
            return i;
        }
    }
    
    return -1;
}

int *build_adjacency_table1(const struct Mesh *m){
    return -1; 
}