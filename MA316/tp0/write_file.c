#define _USE_MATH_DEFINES
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif


#define MAX_LINE_SIZE 1000

int main(int argc, char *argv[]){


    if (argc < 2){
        printf("Please only provide one interger as input \n");
        return 0;
    }else{
        int n = atoi(argv[1]);

        float x_min = - 6 * M_PI;
        float x_max = 6 * M_PI;

        float xs[MAX_LINE_SIZE];
        float ys[MAX_LINE_SIZE];

        float delta_x = (x_max - x_min) / (n - 1);
        
        for(int j = 0; j < n; j++){
            xs[j] = x_min + j * delta_x;
            if(xs[j] == 0){
                ys[j] = 1;
            }else{
                ys[j] = sin(xs[j]) / xs[j];
            }
            
        }

        FILE* fp;
        fp = fopen("series.txt", "w");

        if(fp == NULL){
            printf("Unable to create file");
            return 0;
        }else{
            printf("Output file created succesfully");
        }



        for (int i = 0; i < n ; i++){
            fprintf(fp,"%f\t%f \n", xs[i],ys[i]);
        }


        
    }


    return 0;
}