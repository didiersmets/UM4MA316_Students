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

int tris_are_neighbors(int tri1, int tri2, const struct Mesh *m){
    //On suppose que deux points de vertices ne possèdent pas les mêmes coordonnées
    //On suppose que deux points d'un même triangle ne sont pas identiques



    if (tri1>m->ntri || tri2>m->ntri){
        fprintf(stdout,"erreur : indices trop grands par rapport au nombre de triangles\n");
    }
    int i = 0;
    int j = 0;
    int save_indice_vertices_tri1[2];
    int save_indice_vertices_tri2[2];
    save_indice_vertices_tri1[0]=-1;
    save_indice_vertices_tri1[1]=-1;

    while(i<3){
        while(j<3){
            if(m->triangles[tri1].idx[i]==m->triangles[tri2].idx[j]){
                //ils partagent un même point
                if (save_indice_vertices_tri1[0]==-1){
                    //un point commun entre les deux tri a-t-il déjà été trouvé ? 
                    save_indice_vertices_tri1[0]=i;
                    save_indice_vertices_tri2[0]=j;
                } else {
                    save_indice_vertices_tri1[1]=i;
                    save_indice_vertices_tri2[1]=j;
                }
                break;
            }
            j++;
        }
        i++;
        j=0;
    }
    if (save_indice_vertices_tri1[1]==-1){
        return -1;
    }

    fprintf(stdout,"save_indice_vertices_tri1[0] = %d\n",save_indice_vertices_tri1[0]);
    fprintf(stdout,"save_indice_vertices_tri1[1] = %d\n",save_indice_vertices_tri1[1]);
    fprintf(stdout,"save_indice_vertices_tri2[0] = %d\n",save_indice_vertices_tri2[0]);
    fprintf(stdout,"save_indice_vertices_tri2[1] = %d\n",save_indice_vertices_tri2[1]);


    //calcul de l'orientation

    //on nomme deux sens :
    // si 1, alors v1->v2
    // si 2, alors v2->v1

    int sens_tri1 = (edge_pos_in_tri(m->triangles[tri1].idx[save_indice_vertices_tri1[0]],
    m->triangles[tri1].idx[save_indice_vertices_tri1[1]], m->triangles[tri1]) != -1) ? 1 : 2 ;

    int sens_tri2 = (edge_pos_in_tri(m->triangles[tri2].idx[save_indice_vertices_tri2[0]],
    m->triangles[tri2].idx[save_indice_vertices_tri2[1]], m->triangles[tri2]) != -1) ? 1 : 2;

    printf("sens1 = %d sens2 = %d\n",sens_tri1, sens_tri2);

    if (sens_tri1 == sens_tri2){
        //même sens, donc pas voisins
        return -1;
    } else {
        if (sens_tri1 == 1){
            return edge_pos_in_tri(m->triangles[tri1].idx[save_indice_vertices_tri1[0]],
    m->triangles[tri1].idx[save_indice_vertices_tri1[1]], m->triangles[tri1]);
        } else {
            return edge_pos_in_tri(m->triangles[tri1].idx[save_indice_vertices_tri1[1]],
    m->triangles[tri1].idx[save_indice_vertices_tri1[0]], m->triangles[tri1]);
        }
    }
    

}
