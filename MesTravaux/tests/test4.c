#include <stdio.h>


//test du n=1

int main(){
    FILE *f = fopen("test.txt","r");
     if (f==NULL){
        printf("erreur\n");
        return 0;
    }

    char buffer[256];
    char *res = fgets(buffer, 1, f);
   

    while (res!=NULL){
        res = fgets(buffer, 2, f);
        if (res!=NULL){
        printf("%s",res);}
        printf(",");
    }
 printf("\n");
}

//pourquoi ça sépare de 1 et pas de 2