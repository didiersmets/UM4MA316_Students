#include <stdio.h>
#include "mesh.h"
#include "hash_tables.h"


struct Edge {
    int v1;
    int v2;
};

int edge_pos_in_tri(int v1, int v2, struct Triangle t){
    if(t.idx[0]==v1 && t.idx[1]==v2)
        return 0;
    if(t.idx[1]==v1 && t.idx[2]==v2)
        return 1;
    if(t.idx[2]==v1 && t.idx[0]==v2 )
        return 2;
    return -1;
}


int tris_are_neighbors(int tri1, int tri2, const struct Mesh *m){
    struct Triangle t1 = m->triangles[tri1];
    struct Triangle t2=m->triangles[tri2];
    for(int i=0;i<3;i++){
        int v1=t1.idx[i%3];
        int v2=t1.idx[(i+1)%3];
        if(edge_pos_in_tri(v2,v1,t2)!=-1){
            return i;
        } 
    }
    return -1;
}



int *build_adjacency_table1(const struct Mesh *m){
    int *adjacency=malloc(sizeof(int)*(3*m->ntri));
    for(int i=0;i<3*m->ntri;i++){
        adjacency[i]=-1;
    }
    for(int i=0;i<m->ntri;i++){
        for(int j=0;j<m->ntri;j++){
            if(i!=j){
                int edge = tris_are_neighbors(i, j, m);
                if(edge!=-1){
                    adjacency[(3*i + edge)]=j;
                }
            }
        }
    }
    return adjacency;
}

struct HashTable *build_edge_table1(const struct Mesh *m){
    struct HashTable *hash=malloc(sizeof(struct HashTable));
    for(int i=0;i<m->ntri;i++){
        struct Triangle t=m->triangles[i];
        struct Edge edge[3];

        edge[0].v1 = t.idx[0];
        edge[0].v2 = t.idx[1];

        edge[1].v1 = t.idx[1];
        edge[1].v2 = t.idx[2];

        edge[2].v1 = t.idx[2];
        edge[2].v2 = t.idx[0];
        for(int j=0;j<3;j++){
            struct Edge clé= edge[j];
            int valeur = i;
            hash_table_insert(hash,(void *)&clé,&valeur);
        }
    }
    return hash;
}


int *build_adjacency_table2(const struct Mesh *m){
    int *adjacency=malloc(sizeof(int)*(3*m->ntri));
    struct HashTable *hash=malloc(sizeof(struct HashTable));
    struct HashTable *ht=build_edge_table1(hash);
    for(int i=0;i<3*m->ntri;i++){
        adjacency[i]=-1;
    }
    for(int i=0;i<m->ntri;i++){
            struct Triangle t=m->triangles[i];
            for(int j=0;j<3;j++){
                struct Edge edge;
                edge.v1=t.idx[j/3];
                edge.v1=t.idx[(j+1)/3];
                int *value = hash_table_find(ht,(void *)&edge);
                adjacency[3*i+*value]=j;
            }

    }
    return adjacency;
}