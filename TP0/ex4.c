#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char *argv[]) {

    if (argc != 2) {
        printf("Usage: %s n\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);

    if (n < 2) {
        printf("n must be at least 2\n");
        return 1;
    }

    double pi = acos(-1.0);

    double xmin = -6.0 * pi;
    double xmax =  6.0 * pi;

    double dx = (xmax - xmin) / (n - 1);

    FILE *file = fopen("output.txt", "w");

    if (file == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    for (int j = 0; j < n; j++) {

        double x = xmin + j * dx;
        double y;

        if (fabs(x) < 1e-12) {
            y = 1.0;
        } else {
            y = sin(x) / x;
        }

        fprintf(file, "%f\t%f\n", x, y);
    }

    fclose(file);

    return 0;
}