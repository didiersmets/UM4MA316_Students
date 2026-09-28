#include "../include/mesh_adjacency.h"
#include <stdio.h>
#include <stdlib.h>

int edge_pos_in_tri(int v1, int v2, struct Triangle t){


    // v1/v2/v3 sont des indices d'un tableau de vertex

    if ((t.v1 == v1) && ( t.v2 == v2)){ 
        return 0;
        } else if ((t.v2 == v1) && ( t.v3 == v2)){
            return 1;
        } else if ((t.v3 == v1) && ( t.v1 == v2)) {
            return 2;
        }  else {
        return -1;
    }
    return 0;
}


