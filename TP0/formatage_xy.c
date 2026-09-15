#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int main (int argc, char* argv[]){
    int n = atoi(argv[1]);
    float delta = 12*M_PI/(n-1);

    FILE * file = fopen("result.txt","w");
    if(file==NULL) return -1;


    float x,y;

    for (int i=0;i<n;i++){
        x = -6*M_PI + i*delta;
        if (x==0){
            y = 1;
        }
        y = sin(x)/x;
        fprintf(file,"%f  %f\n", x,y);
    }
    fclose(file);
    return 0;
}