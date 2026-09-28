#include "../include/mesh_adjacency.h"
#include <stdio.h>
#include <stdlib.h>

int edge_pos_in_tri(int v1, int v2, struct Triangle t){


    /////// oops v1/v2/v3 sont des indices d'un tableau de vertex


    /*if ((t.v1 == v1) && ( t.v2 == v2)){ 
        return 0;
        } else if ((t.v2 == v1) && ( t.v3 == v2)){
            return 1;
        } else if ((t.v3 == v1) && ( t.v1 == v2)) {
            return 2;
        }  else {
        return -1;
    }*/
    return 0;
}




int main(){


    struct Mesh *Tableau = malloc(sizeof(Mesh));
    initialize_mesh(Tableau); //free déjà mis à la suite


    //insertion de quelques sommets
    Struct Vertex Vertext_1, Vertex_2, Vertex_3, Vertex_4 = malloc(sizeof(Vertex));
    
    write_mesh_to_medit_file(Tableau,"Test1.mesh");





    dispose_mesh(Tableau);

   /* struct Triangle *t1 = malloc(sizeof(struct Triangle));
    t1->v1 = 1;
    t1->v2 = 2;
    t1->v3 = 3;
    fprintf(stdout,"%d  %d  %d\n",t1->v1,t1->v2,t1->v3);
    fprintf(stdout,"%d\n", edge_pos_in_tri(3,1,*t1));*/
    return 0;
}