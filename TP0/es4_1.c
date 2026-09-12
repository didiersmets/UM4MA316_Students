#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char *argv[]) {

    int n = atoi(argv[1]);

    float xmin = -6 * M_PI;
    float xmax = 6 * M_PI;
    float delta = (xmax - xmin) / (n - 1);

    float x[n];
    float y[n];

    FILE *output;
    output = fopen("output.txt", "w");

    for(int i = 0; i < n; i++) {
        x[i] = xmin + i * delta;
        y[i] = x[i] == 0 ? 1 : sin(x[i])/x[i];
        fprintf(output, "%f\t%f\n", x[i], y[i]);
    }

}