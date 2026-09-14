#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//first argument is n
int main(int argc, char *argv[]){

    int n = atoi(argv[1]);
    float x_min = -6*M_PI;
    float x_max = 6*M_PI;
    float delta_x = (x_max - x_min)/(n-1);

    float x[n];
    float y[n];

    FILE *fptr;
    fptr = fopen("output.txt", "w");

    for(int j=0;j<n;j++){
        x[j] = x_min + j*delta_x;
        y[j] = x[j]==0 ? 1 : sin(x[j])/x[j];
        fprintf(fptr, "%f   %f\n", x[j], y[j]);
    }

    fclose(fptr);

    return 0;
}