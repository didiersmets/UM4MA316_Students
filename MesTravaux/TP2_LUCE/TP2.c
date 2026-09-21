#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>
#include <time.h>

typedef struct Vertex{
    double x;
    double y;
}Vertex;

typedef struct Triangle{
    int index_pt1;
    int index_pt2;
    int index_pt3;
}Triangle;

typedef struct Mesh2D{
    int nv; //number of vertices in the mesh
    Vertex *vert;

    int nt; //Number of triangles in the msh
    Triangle *tri;
}Mesh2D;

int initialize_mesh2D(struct Mesh2D* m, int vtx_capacity, int tri_capacity){
    m->nv = vtx_capacity;
    m->nt = tri_capacity;
    m->vert = malloc(sizeof(Vertex)*m->nv);
    m->tri = malloc(sizeof(Triangle)*m->nt);

    if (!m->vert || !m->tri || !m){
        return 0;
    }
    return 1;
}

void dispose_mesh2D(struct Mesh2D*m){
    if (!m) return;
    free(m->vert);
    free(m->tri);
    free(m);
}

double area_mesh2D(struct Mesh2D* m){ //je comprends que c'est la somme de l'air de chaque triangle de mesh2D

    double aire_totale = 0;

    for(int i=0; i<(m->nt); i++){

        Vertex A = m->vert[(m->tri[i]).index_pt1]; //points A,B et C du trangle i
        Vertex B = m->vert[(m->tri[i]).index_pt2];
        Vertex C = m->vert[(m->tri[i]).index_pt3];

        Vertex AB; //vecteur AB
        AB.x = B.x - A.x;
        AB.y = B.y - A.y;

        Vertex AC;
        AC.x = C.x - A.x;
        AC.y = C.y - A.y;

        aire_totale += 0.5*(AB.x*AC.y-AC.x*AB.y); //déterminant de la matrice composée des vecteurs colonnes AB et AC, qui divisé par 2 donne l'aire signé du trangle ABC
    }

    return aire_totale;
}

int read(struct Mesh2D* m, const char* filename){
    FILE *f = fopen(filename,"r");
    if (!f){
        printf("fichier non ouvert\n");
        exit(1);
    }

    //on voit dans les fichiers mesh à disposition que la dimension est 3, on a 5 points de 3 coordonnées, et 4 triangles, formant, une pyramide à base triangulaire
    //nous allons alors prendre les valeurs en oubliant la 3ème coordonnée
    char buffer[256];
    char mot[256];
    char* res=""; //je l'initialise car parfois il s'auto initialise à NULL et n'entre pas dans la boucle

    while ((strcmp(mot,"Vertices")!=0) && res!=NULL){ //strcmp == 0 si les deux chaines de caractères mises en argument sont identiques
        res = fgets(buffer, 256, f);
        sscanf(buffer, "%s", mot);
    }
    if (res == NULL) printf("Pas de 'Vertices' dans ton fichier\n");

    int previous_nv = m->nv;
    sscanf(buffer, "%s %d", mot, &(m->nv));
    if ((m->nv)>previous_nv){
        printf("Veuillez initialisez mesh en mettant en second argument un nombre >=%d\n",m->nv);
        return 0;
    }

    //printf("vertices number : %d\n", m->nv);

    Vertex *point = malloc(sizeof(Vertex));
    char str[256];
    strcpy(str,""); //recopie le contenu du deuxième argument dans le premier (initialise str à une chaine de charactère vide)
    int j;
    int k=0;
    int index = 0; //indice pour le tableau str


    for(int i=0; i<m->nv;i++){ //i représente les lignes où se trouve les coordonnées des points

        j=0;
        k=0;

        fgets(buffer, 256, f); //recopie une ligne de f et la met dans buffer

        while (k<2){
            while( buffer[j]!='\0' && j<256 && buffer[j]==' '){ //je skip les espaces      
                j++;
            }
            while( buffer[j]!='\0' && j<256 && buffer[j]!=' '){ //si ce n'est pas la fin de la ligne, on a donc une suite de nombre à mettre dans str     
                str[index]=buffer[j];
                index++;
                j++;
            }
            //maintenant soit on a un nouveau un espace, soit c'est la fin de la ligne et donc str est un nombre (écrit en char*)
            if (k==0) {
                sscanf(str, "%lf",&(point->x));
            }
            if (k==1){
                sscanf(str, "%lf",&(point->y));
                m->vert[i]=*point; //après avoir assigné les valeurs dans point, je mets point dans le tableau
            }
            index =0;
            strcpy(str,"");
            k++;
        }
    
    }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///Partie pour prendre les coordonnées du triangle///

    Triangle *tritri = malloc(sizeof(Triangle)); 

    while ((strcmp(mot,"Triangles")!=0) && res!=NULL){  //même si je sais que c'est juste à la ligne d'après, on sait jamais
        res = fgets(buffer, 256, f);
        sscanf(buffer, "%s", mot);
    }
    if (res == NULL) printf("Pas de 'Triangles' dans ton fichier\n");
    int previous_nt = m->nt;
    sscanf(buffer, "%s %d", mot, &(m->nt));
    if ((m->nv)>previous_nt){
        printf("Veuillez initialisez mesh en mettant en troisième argument un nombre >=%d\n",m->nt+1);
        return 0;
    }

//    fprintf(stdout, "triangle number : %d\n",m->nt); //fprintf(stdout,...) pour le fun (et pour retenir/apprendre)

    strcpy(str,"");
    index = 0;

   for(int i = 0; i<m->nt; i++){
        k=0;
        j=0;
        fgets(buffer, 256, f);
        while(k<3){
            while( buffer[j]!='\0' && j<256 && buffer[j]==' '){
                j++;  
            }
            while( buffer[j]!='\0' && j<256 && buffer[j]!=' '){
                str[index++]=buffer[j];
                j++;
            }
            if (k==0){
                sscanf(str,"%d",&(tritri->index_pt1));
            }
            if (k==1){
                sscanf(str,"%d",&(tritri->index_pt2));
            }
            if (k==2){
                sscanf(str,"%d",&(tritri->index_pt3));
                (m->tri)[i]=*tritri;
            }
            index = 0;
            k++;
            strcpy(str,"");
        }
    }


    fclose(f);
    return 1;
}

int mesh2D_to_gnuplot(struct Mesh2D* m, const char* filename){

    FILE *f = fopen(filename,"w");
    
    for(int i=0; i<m->nt;i++){

        fprintf(f,"%lf %lf\n", m->vert[(m->tri)[i].index_pt1-1].x, m->vert[(m->tri)[i].index_pt1-1].y);
        fprintf(f,"%lf %lf\n", m->vert[(m->tri)[i].index_pt2-1].x, m->vert[(m->tri)[i].index_pt2-1].y);
        fprintf(f,"%lf %lf\n", m->vert[(m->tri)[i].index_pt3-1].x, m->vert[(m->tri)[i].index_pt3-1].y);
        fprintf(f,"%lf %lf\n", m->vert[(m->tri)[i].index_pt1-1].x, m->vert[(m->tri)[i].index_pt1-1].y); //copie du premier point, reliant le dernier à celui ci
    }
     fclose(f); //il est important de fclose avant d'utiliser gnuplot, afin de sauvegarder ce qu'on a mis dans le fichier



    char buffer[50000];
    //snprintf permet de concaténer le troisième argument au buffer en s'assurant que la taille du résultat ne dépasse pas la mémoire allouée pour le buffer
    //attention snprintf écrase ce qu'il y avait dans buffer, sprintf renvoie également un int, donnant le nombre de caractère dans buffer après la concaténation

    int nb=0;

    nb += snprintf(buffer, sizeof(buffer), "gnuplot -persist -e \""
        "set xrange [-1:2];"
        "set yrange [-1:2];"
        "set ylabel 'y';"
        "set xlabel 'x';"); 


    for(int i = 0; i<m->nt;i++){
        if (i==0){
            nb += snprintf(buffer+nb, sizeof(buffer)-nb, "plot '%s' using 1:2 with linespoints title 'triangle %d',",filename,i+1);
        } if(i==(m->nt-1)){
            nb += snprintf(buffer+nb, sizeof(buffer)-nb, "'%s' every ::%d::%d using 1:2 with linespoints title 'triangle %d';",filename, i*4, i*4+3,i+1);
            //je lis les lignes qui concerne mon triangle
        } else {
            nb += snprintf(buffer+nb, sizeof(buffer)-nb, "'%s' every ::%d::%d using 1:2 with linespoints title 'triangle %d',",filename,i*4,i*4+3,i+1); 
        }
    }
    snprintf(buffer+nb, sizeof(buffer)-nb,"\"");
    printf("nb = %d\n",nb);

    system(buffer);
    
    return 1;

}

int write_mesh2D(struct Mesh2D* m, const char* filename){
    FILE *f=fopen(filename,"w");
    fprintf(f,"MeshVersionFormatted 2\n");
    fprintf(f,"Dimension 2\n");
    fprintf(f,"Vertices %d\n",m->nv);
    for(int i =0; i<m->nv;i++){
        for(int k=0;k<20;k++){
        fprintf(f," ");
        }
        fprintf(f,"                         ");
        fprintf(f,"%.1lf", ((m->vert)[i]).x);
        fprintf(f,"                         ");
        fprintf(f,"%.1lf", ((m->vert)[i]).y);
        fprintf(f,"\n");
    }
    fprintf(f,"Triangles %d\n",m->nt);
    for(int i=0; i<m->nt;i++){
        fprintf(f,"%d",((m->tri)[i]).index_pt1);
        fprintf(f," %d",((m->tri)[i]).index_pt2);
        fprintf(f," %d",((m->tri)[i]).index_pt3);
        fprintf(f," 1\n");
    }
    fprintf(f,"End\n");
    fclose(f);
    return 1;
}

int main(){
    Mesh2D *m = malloc(sizeof(Mesh2D)); 
    int d = initialize_mesh2D(m,5,5);
    if (d==0) printf("zut\n");
    read(m,"mesh1-tp2.mesh");
    write_mesh2D(m,"salut.mesh");

    /*                    TEST(ça fonctionne)
    
    for(int i =0; i<5; i++){ 
        printf("(%.1lf,%.1lf)\n",(m->vert[i]).x,(m->vert[i]).y);
    }
    for(int i =0; i<4; i++){
        printf("(%d,%d,%d)\n",(m->tri[i]).index_pt1,(m->tri[i]).index_pt2, (m->tri[i]).index_pt3);
    }
    */

    Mesh2D *m2 = malloc(sizeof(Mesh2D));
    int e = initialize_mesh2D(m2,1000,1000);
    if (e==0) printf("zut\n");

    read(m2,"mesh2-tp2.mesh");
    write_mesh2D(m2,"salut2.mesh"); 

    mesh2D_to_gnuplot(m,"mesh1");


    dispose_mesh2D(m);
    dispose_mesh2D(m2);


    return 0;
}