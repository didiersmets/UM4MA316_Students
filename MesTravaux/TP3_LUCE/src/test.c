#include "../include/hash_tables.h"
#include "../include/mesh_adjacency.h"
#include "../include/mesh.h"
#include "../include/mesh.h"




int main(){


    struct Mesh *Tableau = malloc(sizeof(Mesh));
    initialize_mesh(Tableau); //free déjà mis à la suite

    read_mesh_from_medit_file(Tableau, "Test1.mesh");






    dispose_mesh(Tableau);

   /* struct Triangle *t1 = malloc(sizeof(struct Triangle));
    t1->v1 = 1;
    t1->v2 = 2;
    t1->v3 = 3;
    fprintf(stdout,"%d  %d  %d\n",t1->v1,t1->v2,t1->v3);
    fprintf(stdout,"%d\n", edge_pos_in_tri(3,1,*t1));*/
    return 0;
}