int read_mesh2D(struct Mesh2D* m, const char* filename);

File * f = fopen( );
char line[256];

while (fgets(line, 256, f)){
    int nv;
    if (sscanf(line, "Vertices %d", &nv)==1){

        // reserver memoire
        m -> vert = malloc(nv * sizeof(struct Vertex));
        if (m ->vert == NULL) {
            break;
        }

        // lire les vtx
        int 


        for (int i =0; i < nv; i++) {
            fgets(line, 256, f);
            double x, y;
            sscanf(line, "%lf %lf", &x, &y);
            m->vert[i].x = x;
            m->vert[i].y = y;
            m->vert[i].z = z;


        }

    }

}

fclose(f);
