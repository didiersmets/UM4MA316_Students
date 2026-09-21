#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char *argv[]) {
	if (argc < 2) {
return 1;
}

	int n = atoi(argv[1]);

FILE *file = fopen("sinc.txt", "w");

if (file  ==NULL) {
return 1;
}

double x_min = -6 * M_PI;
double x_max = +6 *M_PI;
double diffmax = (x_max - x_min)/(n-1);


for (int i = 0; i < n; i++) {
double x = x_min + i * diffmax;
double y;
if (fabs(x) < 1e-12) {
y = 1.0;
}
else {
y = sin(x)/x;
}

fprintf(file, "%f\t%f\n", x,y);
}

fclose(file);


return 0;
}

