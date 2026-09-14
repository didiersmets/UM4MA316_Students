#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//first argument is n
int main(int argc, char *argv[]){

    int n = atoi(argv[1]);
    double x_min = -6*M_PI;
    double x_max = 6*M_PI;
    double delta_x = (x_max - x_min)/(n-1);

    double* x = (double*)malloc(n * sizeof(double));
    double* y = (double*)malloc(n * sizeof(double));

    if(x == NULL || y == NULL){
        printf("Error allocating memory");
        return 1;
    }

    FILE *fptr;
    fptr = fopen("4.2.txt", "w");

    for(int j=0;j<n;j++){
        x[j] = x_min + j*delta_x;
        y[j] = x[j]==0 ? 1 : sin(x[j])/x[j];
        fprintf(fptr, "%f   %f\n", x[j], y[j]);
    }
    
    fclose(fptr);
    free(x);
    free(y);

    return 0;
}