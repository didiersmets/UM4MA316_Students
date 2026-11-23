#include "../include/hash_tables.h"
#include "../include/mesh_adjacency.h"
#include "../include/mesh.h"
#include "../include/mesh_io.h"
#include <stdio.h>
#include <stdlib.h>


//gcc hash_tables.c main.c mesh_adjacency.c mesh_io.c mesh.c -o test
//ne pas oublier : soit i un nombre du mesh représentant l'indice d'un des triangles
//alors le point correspondant sera vertices[i-1]
//On suppose que deux points de vertices ne possèdent pas les mêmes coordonnées
//On suppose que deux points d'un même triangle ne sont pas identiques





int main(){


    struct Mesh *Tableau = malloc(sizeof(struct Mesh));
    initialize_mesh(Tableau); //free déjà mis à la suite
    read_mesh_from_medit_file(Tableau, "Test1.mesh");

    /*démonstration du ne pas oublier :                         CONCLUSION : C'est bon
    (3 == Tableau->triangles[0].idx[2]) ? printf("C'est bon \n") : printf("C'est pas bon");
    (2 == Tableau->triangles[0].v2) ? printf("C'est bon \n") : printf("C'est pas bon");
    */

    
    /*test edge_pos_in_tri      OK
    fprintf(stdout, "%d \n",edge_pos_in_tri(Tableau->triangles[4].v3,Tableau->triangles[4].v1,Tableau->triangles[3]));
    fprintf(stdout, "%d \n",edge_pos_in_tri(Tableau->triangles[1].v1,Tableau->triangles[1].v2,Tableau->triangles[1]));
    fprintf(stdout, "%d \n",edge_pos_in_tri(Tableau->triangles[0].v2,Tableau->triangles[0].v3,Tableau->triangles[0]));
    fprintf(stdout, "%d \n",edge_pos_in_tri(Tableau->triangles[4].v3,Tableau->triangles[4].v1,Tableau->triangles[4]));*/


    /*test  tris_are_neighbors OK
    //j'ai rajouté  un 5e triangle dans le mesh de sorte à ce qu'il soit voisin 
    //avec le premier

    int pos = tris_are_neighbors(0,5,Tableau);
    int pos2 = tris_are_neighbors(1,6,Tableau);
    int pos3 = tris_are_neighbors(4,5,Tableau);

    ( pos == -1) ? printf("pas voisin\n") : printf("voisin\n"); //voisin comme prévu
    printf("%d\n",pos);

    ( pos2 == -1) ? printf("pas voisin\n") : printf("voisin\n"); //voisin comme prévu
    printf("%d\n",pos2);

    ( pos3 == -1) ? printf("pas voisin\n") : printf("voisin\n"); //pas voisin comme prévu
    printf("%d\n",pos3);
    */

    //test build_adjacency_table1

    int* Tableau_adjacence = build_adjacency_table1(Tableau);

    //si ça fonctionne comme il faut comme triangle 0 et 5 sont voisins,  
    //le common edge est en position 1, donc on s'attend à Tableau_adjacence[0+1] = 5

    //printf("Tableau_adjacence[1] = %d\n", Tableau_adjacence[1]);
    //free(Tableau_adjacence);



    dispose_mesh(Tableau);
    return 0;
}