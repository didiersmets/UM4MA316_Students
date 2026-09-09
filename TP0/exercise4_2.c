#include <stdio.h>
#include <stdlib.h>
#include <math.h>


void exercise(int n){
    
    double xmin = -6 * M_PI;
    double xmax = 6 * M_PI;
    double diffx = (xmax - xmin)/(n-1);
    double x = xmin;
    double y = sin(x)/x;

    printf("%f\t%f\n", x, y);

    for (int i=1; i < n; i++){
        x = xmin + i*(diffx);
        
        if (x==0){
            y = 1;
        } else {
            y = sin(x)/x;
        }

        printf("%f\t%f\n", x, y);
    }

}

int main(int argc, char *argv[]){
    exercise(atoi(argv[1]));
    return 0;
}