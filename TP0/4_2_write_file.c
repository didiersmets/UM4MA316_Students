#define _USE_MATH_DEFINES
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define MAX_LINE_SIZE 1000

#define get_index(i,j) (((i) * (n)) + (j))

#define OUTPUT_FILE_NAME "series.txt"

int main(int argc, char *argv[]){


    if (argc < 2){
        printf("Please only provide one interger as input \n");
        return 1;
    }else{
        int n = atoi(argv[1]);

        if(n <= 1 || n > MAX_LINE_SIZE){
            printf("Please provide a number greater than 1\n");
            return 1;
        }

        double x_min = - 6 * M_PI;
        double x_max = 6 * M_PI;

        double *xs = malloc(n * sizeof(double));
        double *ys = malloc(n * sizeof(double));

        if(xs != NULL && ys != NULL){

            double delta_x = (x_max - x_min) / (n - 1);
        
            for(int j = 0; j < n; j++){
                xs[j] = x_min + j * delta_x;
                if(fabs(xs[j]) < 1e-6){ //zero checking with double noise
                    ys[j] = 1;
                }else{
                    ys[j] = sin(xs[j]) / xs[j];
                }
                
            }

            FILE* fp;
            fp = fopen(OUTPUT_FILE_NAME, "w");

            if(fp == NULL){
                printf("Unable to create file");
                return 0;
            }else{
                printf("Output file created succesfully\n");
            }



            for (int i = 0; i < n ; i++){
                fprintf(fp,"%f\t%f \n", xs[i],ys[i]);
            }
            
            fclose(fp);

            free(xs);
            free(ys);
        }



        
    }


    return 0;
}