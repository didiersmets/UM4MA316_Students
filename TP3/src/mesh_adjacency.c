#include "mesh_adjacency.h"

int edge_pos_in_tri(int v1, int v2, struct Triangle t) {
    for ( int j =0 ; j< 3 ; j++) {
        int depart = t.idx[j];
        int arrivee = t.idx[(j+1)%3]; // mod 3 pour pas sortir du tableau
        if (depart == v1 && arrivee == v2) {
            return j;
        }
    }
    return - 1;
}


int tris_are_neighbors(int tri1, int tri2, const struct Mesh *m) {
    struct Triangle t1 = m->triangles[tri1];
    struct Triangle t2 = m->triangles[tri2];

    for (int j =0; j<3; j++) {
        int a = t1.idx[j]; //depart de l'arete j de tri1
        int b = t1.idx[(j+1) %3]; // arrivee de l'arete j de tri1
        if (edge_pos_in_tri(b, a, t2) != -1) //b->a est dans tri2
            return j;
    }
    return -1; 

}

int *build_adjacency_table1(const struct Mesh *m) {

	int n = 3 * m->ntri;        

	int *adj_table = malloc(n * sizeof(int)); 
     
    if(adj_table == NULL){
        return NULL;
    }

	for (int c = 0; c < n; c++)
		adj_table[c] = -1;

	for (int i = 0; i < m->ntri; i++) {     
		for (int k = 0; k < m->ntri; k++) {    
			if (i == k)
				continue;                       // un triangle n'est pas son propre voisin
			int edge = tris_are_neighbors(i, k, m);
			if (edge != -1)
				adj_table[3 * i + edge] = k;
		}
	}
	return adj_table;    

}