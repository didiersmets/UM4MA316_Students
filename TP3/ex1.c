int edge_pos_in_tri (int v1, int v2, struct Triangle t) {
	if (v1==t.x && v2==t.y){
		return 0;
	}else if (v1==t.y && v2==t.z){
		return 1;
	}else if (v1==t.z && vé==t.x){
		return 2;
	}
	return -1;
}

int tris_are_neighbors (int tri1, int tri2, const struct Mesh *m){
	int v0 = edge_pos_in_tri(tri2.y, tri2.x, tri1);
	int v1 = edge_pos_in_tri(tri2.z, tri2.y, tri1);
	int v2 = edge_pos_in_tri(tri2.x, tri2.z, tri1);
	if (v0!=-1){
		return v0;
	}else if (v1!=-1){
		return v1;
	}
	return v2;
}



