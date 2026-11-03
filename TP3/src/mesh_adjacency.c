#include <string.h>
#include <stdlib.h>

#include "mesh_adjacency.h"

// Exercises 2-6

int edge_pos_in_tri(int v1, int v2, struct Triangle t){
    int a = t.v1;
    int b = t.v2;
    int c = t.v3;
    //verify if present
    if(v1 == a){
        if(v2 == b){
            return 0;
        }else{
            return -1;
        }
    }else if(v1 == b){
        if(v2 == c){
            return 1;
        }else{
            return -1;
        }
    }else if(v1 == c){
        if(v2 == a){
            return 2;
        }else{
            return -1;
        }
    }else{
        return -1;
    }
}


int tris_are_neighbors(int tri1, int tri2, const struct Mesh *m){
    // if they share a common edge with opposite orientations
    struct Triangle t1 = m->triangles[tri1];
    struct Triangle t2 = m->triangles[tri2];
    // for edges of t1
    for(int i = 0; i < 3; i++){
        int v1 = t1.idx[i];
        int v2 = t1.idx[(i + 1) % 3];
        //int pos_et1 = edge_pos_in_tri(v1, v2, t1);
        int pos_et2 = edge_pos_in_tri(v2, v1, t2);
        if(pos_et2 != -1){
            return i;
        }
    }
    return -1;    
}


int *build_adjacency_table1(const struct Mesh *m){
    //allocate the table
    int *adjacency_table = malloc(3 * m->ntri * sizeof(int));
    if(adjacency_table == NULL){
        return NULL;
    }
    //initialize to 0;
    memset(adjacency_table, -1, 3 * m->ntri * sizeof(int));

    for(int i = 0; i < m->ntri; i++){
        for(int j = 0; j < m->ntri; j++){
            if(i == j){
                continue;
            }
            int edge = tris_are_neighbors(i,j,m);
            if(edge != -1){
                adjacency_table[3 * i + edge] = j;
            }
        }
    }
    return adjacency_table;
}

struct HashTable *build_edge_table1(const struct Mesh *m){
    int ntri = m->ntri;
    int key_len = sizeof(struct Edge);
    int val_len = sizeof(int);
    struct HashTable *ht  = hash_table_init(6 * m->ntri,key_len, val_len);
    if(ht == NULL){
        return NULL;
    }
    //for all the triangles
    for(int k = 0; k < ntri; k++){
        struct Triangle t = m->triangles[k];
        //extract their edges as vertex pairs and insert them into the table
        for(int i = 0; i < 3; i++){
            struct Edge key;
            key.v1 = t.idx[i];
            key.v2 = t.idx[(i + 1) % 3];
            int val = k;
            hash_table_insert(ht,&key, &val);
        }
    }
    return ht;
}


int *build_adjacency_table2(const struct Mesh *m){
        //allocate the table
    int *adjacency_table = malloc(3 * m->ntri * sizeof(int));
    if(adjacency_table == NULL){
        return NULL;
    }
    struct HashTable *he_t = build_edge_table1(m);
    //initialize to 0;
    memset(adjacency_table, -1, 3 * m->ntri * sizeof(int));

    int n = m->ntri;
    // for all triangles
    for(int i = 0; i < n; i++){
        struct Triangle t = m->triangles[i];
        //check if the inverse pair is in the hashtable
        for(int j = 0; j < 3; j++){
            struct Edge key;
            //invert the vertex in the key lookup
            key.v2 = t.idx[j];
            key.v1 = t.idx[(j + 1) % 3];
            int *found = hash_table_find(he_t, &key);
            if(found != NULL){
                int val;
                memcpy(&val, found, sizeof val);
                adjacency_table[3 * i + j] = val; // val is properly aligned
            }
        }
    }
    hash_table_fini(he_t);
    free(he_t);
    return adjacency_table;
}


void edge_table_initialize(struct EdgeTable *et, int nvert, int ntri){
    et->head = malloc(nvert * sizeof(int));
    memset(et->head, -1, nvert * sizeof(int));
    et->next = malloc(3 * ntri * sizeof(int));
    memset(et->next, -1, 3 * ntri * sizeof(int));
}

void edge_table_dispose(struct EdgeTable *et){
    free(et->head);
    free(et->next);
}

void edge_table_insert(int v1, int edge_code, struct EdgeTable *et){
    if(et->head[v1] == -1){ //not present
        //push
        et->head[v1] = edge_code; //edge_code is already 3 * i + j
    }else{ //present
        //chain
        int tmp = et->head[v1]; //save the content of head[v1]
        et->head[v1] = edge_code; //insert the new code into head[v1]
        et->next[edge_code] = tmp; //inseer the saved content onto its unique slot next[edge_code]
    }
}

int edge_table_find(int v1, int v2, const struct EdgeTable *et, const struct Mesh *m){
    if(et->head[v1] == -1){
        return -1;
    }else{
        int edge_code = et->head[v1];
        while(edge_code != -1){
            int i = edge_code / 3; // decode index of triangle
            int j = edge_code % 3; // decode edge offset j=0 lands on v2 j=1 lands on v3 j=2 lands on v1
            struct Triangle t = m->triangles[i]; //get triangle
            if(t.idx[(j + 1) %3] == v2){ //check that endpoint of edge is v2
                return edge_code;
            }
            edge_code = et->next[edge_code];
        }
        return -1;
    }
}

struct EdgeTable *build_edge_table3(const struct Mesh *m){

    struct EdgeTable *et = malloc(sizeof(struct EdgeTable));
    edge_table_initialize(et, m->nvert, m->ntri);

    for(int i = 0; i < m->ntri; i++){
        struct Triangle t = m->triangles[i];
        for(int j = 0; j < 3; j++){
            int edge_code = i * 3 + j;
            edge_table_insert(t.idx[j], edge_code, et);
        }
    }
    return et;
}

int *build_adjacency_table3(const struct Mesh *m){

    struct EdgeTable *et = build_edge_table3(m);

    int *adjacency_table = malloc(3 * m->ntri * sizeof(int));
    memset(adjacency_table, -1, 3 * m->ntri * sizeof(int));

    for(int i = 0; i < m->ntri; i++){
        struct Triangle t = m->triangles[i];
        for(int j = 0; j < 3; j++){
            int edge_code = edge_table_find(t.idx[(j+1) % 3], t.idx[j], et, m);
            adjacency_table[3 * i + j] = (edge_code == -1) ? -1 : edge_code / 3; //if the code is not -1 get the triangle index to insert 
        }
    }
    
    edge_table_dispose(et);
    free(et);
    return adjacency_table;
}