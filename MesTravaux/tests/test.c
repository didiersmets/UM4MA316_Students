#include <stdio.h>

#include <math.h>







void area(double a,double b,double c,double d){ 
    printf("aire deter %lf\n", 0.5*(a*d-b*c) );
    printf("aire sans deter %lf\n", 0.5*sqrt((pow(a,2)+pow(b,2))) * sqrt((pow(c,2)+pow(d,2))) * sqrt(1 - pow((a*c + b*d )/(sqrt((pow(a,2)+pow(b,2))) * sqrt((pow(c,2)+pow(d,2)))),2)    ));
   

}





int main(){
    area(22,31,43,52);


    return 1;
}