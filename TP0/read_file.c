
#include <stdio.h>


int main (int argc, char * argv[]){

    FILE *fichier;
    char ligne[1000];


    fichier = fopen(argv[1], "r"); 
    if (fichier==NULL){
        perror("Erreur d'ouverture du fichier");
        return -1;
    }

    
    while (fgets(ligne, 1000, fichier) != NULL){
        puts(ligne);
    }

    fclose(fichier);
    return 0;

}