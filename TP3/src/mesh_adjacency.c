#include "mesh_adjacency.h"
#include <stdlib.h>

// exercice 1
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


// exercice 2
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

// exercice 3
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

// exercice 4
struct HashTable *build_edge_table1(const struct Mesh *m){
    struct HashTable *ht = hash_table_init(6 * m->ntri, sizeof(struct Edge), sizeof(int));

    if (ht == NULL)
        return NULL;

    for (int i =0; i< m->ntri; i++) {
        struct Triangle t = m->triangles[i];
        for (int j =0; j<3; j++) {
            struct Edge e;
            e.v1 = t.idx[j];
            e.v2 = t.idx[(j+1)%3];
            hash_table_insert(ht, &e, &i);
        }
    }
    return ht;

}

// exercice 5
int *build_adjacency_table2(const struct Mesh *m) {
    
    int n = 3 * m->ntri;        

	int *adj = malloc(n * sizeof(int)); 
     
    if(adj == NULL){
        return NULL;
    }

	for (int c = 0; c < n; c++) {
		adj[c] = -1;
    }

    struct HashTable *ht = build_edge_table1(m);
    if (ht == NULL) {
        free(adj);
        return NULL;
    }

    for(int i =0; i<m->ntri; i++) {
        struct Triangle t = m->triangles[i];
        for (int j =0; j<3; j++) {
            struct Edge opp;
            opp.v1 = t.idx[(j+1) %3];
            opp.v2 = t.idx[j];

            int *voisin = hash_table_find(ht, &opp);
            if (voisin != NULL) {
                adj[3*i +j] = *voisin;
            }
        }
    }

    hash_table_fini(ht);
    free(ht);
    return adj;

}


// exercice 6
void edge_table_initialize(struct EdgeTable *et, int nvert, int ntri) {
    et ->head = malloc(nvert * sizeof(int));
    et ->next = malloc(3 * ntri * sizeof(int));

    for (int v = 0; v < nvert; v++)
        et->head[v] = -1;

    for (int c = 0; c < 3 * ntri; c++)
        et->next[c] = -1;
}

void edge_table_dispose(struct EdgeTable *et) {
    free(et->head);
    free(et->next);

    et->head = NULL;
    et->next = NULL;
}

void edge_table_insert(int v1, int edge_code, struct EdgeTable *et) {
    int tmp = et->head[v1];  // ancien sommet de la pile

    et->head[v1] = edge_code; 
    et->next[edge_code] = tmp; 
}

int edge_table_find(int v1, int v2, const struct EdgeTable *et, const struct Mesh *m) {
    int code = et->head[v1];
    while (code != -1) {
        int i = code / 3;
        int j = code % 3;
        int arrivee = m->triangles[i].idx[(j + 1) % 3];
        if (arrivee == v2)
            return code;
        code = et->next[code];  // arete suivante du tiroir v1
    }
    return -1;
}


struct EdgeTable *build_edge_table3(const struct Mesh *m) {
    struct EdgeTable *et = malloc(sizeof(struct EdgeTable));

    if (et == NULL)
        return NULL;

    edge_table_initialize(et, m-> nvert, m->ntri);

    for (int i = 0; i < m->ntri; i++) {
        struct Triangle t = m->triangles[i];

        for (int j = 0; j < 3; j++)
            edge_table_insert(t.idx[j], 3 * i + j, et);
    }

    return et;
}

int *build_adjacency_table3(const struct Mesh *m) {
    int n = 3 * m->ntri;
    int *adj = malloc(n * sizeof(int));
    if (adj == NULL)
        return NULL;
    for (int c = 0; c < n; c++)
        adj[c] = -1;

    struct EdgeTable *et = build_edge_table3(m);
    if (et == NULL) {
        free(adj);
        return NULL;
    }

    for (int i = 0; i < m->ntri; i++) {
        struct Triangle t = m->triangles[i];

        for (int j = 0; j < 3; j++) {
            int a = t.idx[j];
            int b = t.idx[(j + 1) % 3];
            int code = edge_table_find(b, a, et, m);

            if (code != -1)
                adj[3 * i + j] = code / 3;
        }
    }

    edge_table_dispose(et);
    free(et);
    return adj;
}