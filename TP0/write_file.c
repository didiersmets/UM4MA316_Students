#include <stdio.h>
#include <math.h>

int main()
{
    int n;
    
    printf("Enter n:");
    scanf("%d",&n);
    
    if (n<=1){
        printf("n must be greater than 1.\n");
        return 1;
    }
    
    double pi = acos(-1.0);
    
    double xmin =-6.0*pi ;
    double xmax=6.0*pi;
    
    double deltax=(xmax-xmin)/(n-1);
    
    FILE *file = fopen("output.txt", "w");
    
    if (file == NULL){
        printf("Cannot open file.\n");
        return 1;
    }
    
    for (int j=0; j<n; j++){
        double x = xmin + j * deltax;
        double y = sin(x) / x;
        
        fprintf(file, "%f\t%f\n", x, y);
        printf("%f\t%f\n", x, y);
    }
    fclose(file);

    return 0;
    
}

