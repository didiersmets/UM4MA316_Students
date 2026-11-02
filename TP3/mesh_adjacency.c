int edge_pos_in_tri(int v1, int v2, struct Triangle t) {
    for ( int j =0 , j< 3, j++) {
        if (t.idx[j] == v1 || t.idx[j + 1] == v2) {
            return j;
        }
    }
    return - 1
}


int tris_are_neighbors(int tri1, int tri2, const struct Mesh *m) {

    if 
}