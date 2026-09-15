#include <stdio.h>
#include <stdlib.h>

int main(int argc, char * argv[])
{
	FILE*fichier;
	char ligne[1000000];
	fichier = fopen(argv[1], "r");
	if (fichier == NULL) 
	{
		printf("Erreur : impossible de lire le fichier.\n");
	}
	while(fgets(ligne, 1000000, fichier) != NULL)
	{
		printf("%s", ligne);
	}
	fclose(fichier);
	return 0;
}	
