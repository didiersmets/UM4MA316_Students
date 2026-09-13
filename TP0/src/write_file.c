#include <stdio.h>
#include <math.h>
#include <stdlib.h>


int main(int argc, char *argv[]) {

    if (argc != 2) {
        fprintf(stderr, "%s <positive integer>\n", argv[0]);
        return 1;
    }

    char *endptr;
    size_t n;
    n = strtol(argv[1], &endptr, 10);

    FILE *fp;

    fp = fopen("../output.txt", "w");
    double x = -6*M_PI;
    double delta = (6*M_PI - x)/n;
    for (size_t i = 0 ; i < n; i++) {
        fprintf(fp, "%f\t%f\n", x, sin(x)/x);
        x += delta;
    }

    fclose(fp);

    return 0;
}
