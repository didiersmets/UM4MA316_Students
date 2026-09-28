#include "../include/hash_tables.h"
#include "../include/mesh_adjacency.h"
#include "../include/mesh.h"
#include "../include/mesh_io.h"
#include <stdio.h>
#include <stdlib.h>


//gcc hash_tables.c main.c mesh_adjacency.c mesh_io.c mesh.c -o test
//ne pas oublier : soit i un nombre du mesh représentant l'indice d'un des triangles
//alors le point correspondant sera vertices[i-1]



int main(){


    struct Mesh *Tableau = malloc(sizeof(struct Mesh));
    initialize_mesh(Tableau); //free déjà mis à la suite
    read_mesh_from_medit_file(Tableau, "Test1.mesh");

    /*démonstration du ne pas oublier :                         CONCLUSION : C'est bon
    (3 == Tableau->triangles[0].v3) ? printf("C'est bon \n") : printf("C'est pas bon");
    (2 == Tableau->triangles[0].v2) ? printf("C'est bon \n") : printf("C'est pas bon");
    */

    
    /*test edge_pos_in_tri      OK
    fprintf(stdout, "%d \n",edge_pos_in_tri(Tableau->triangles[4].v3,Tableau->triangles[4].v1,Tableau->triangles[3]));
    fprintf(stdout, "%d \n",edge_pos_in_tri(Tableau->triangles[1].v1,Tableau->triangles[1].v2,Tableau->triangles[1]));
    fprintf(stdout, "%d \n",edge_pos_in_tri(Tableau->triangles[0].v2,Tableau->triangles[0].v3,Tableau->triangles[0]));
    fprintf(stdout, "%d \n",edge_pos_in_tri(Tableau->triangles[4].v3,Tableau->triangles[4].v1,Tableau->triangles[4]));*/




    dispose_mesh(Tableau);
    return 0;
}