#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char * argv[])
{
	int n;
	double xmin, xmax, dx;
	double x,y;
	n = atoi(argv[1]);
	xmin = -6*M_PI;
	xmax = 6*M_PI;
	dx = (xmax - xmin)/(n-1);

	FILE*fichier = fopen("resultat.txt", "w");

	if (fichier ==NULL)
	{
		printf("Erreur : impossible de créée le fichier.\n");
		return 1;
	}

	for (int j=0; j<n; j++)
	{
		x = xmin + j*dx;
			if  (x==0)
			{
				y = 1;
			}
			else
			{
				y = sin(x)/x;
			}
		fprintf(fichier, "%f\t%f\n", x, y);
	}
	fclose(fichier);
	return 0;
}
