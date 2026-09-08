#include <stdio.h>
#include <math.h>
#include <stdlib.h>



void Ex4_q2(int n){
    //gcc Exo4.c -o lol -lm
    FILE *f = fopen("exo4q2.text","w");

    if (!f){
        printf("erreur");
        exit(1);
    }

    float xmin = -6*M_PI;
    float xmax = 6*M_PI;
    float delta_x = (xmax-xmin)/(n-1);


    for(int j=0; j<n; j++){
        float xj = xmin + j*delta_x;
        float yj = xj == 0 ? 0.0 : sin(xj)/xj;
        fprintf(f,"%f   %f\n",xj,yj);

    }
}




int main(){

   /* Exo 4 Question 1
   
    FILE *f = fopen("test-tp0.txt","r");
    if (f==NULL){
        printf("erreur\n");
        return 0;
    }

    char buffer[256];
    char *res = fgets(buffer, 3, f);

    while (res!=NULL){
        printf("%s",res);
        res = fgets(buffer, 3, f);
    }
    */
    Ex4_q2(17);
    return 0;       
}