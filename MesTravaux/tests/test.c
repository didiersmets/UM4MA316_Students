#include <stdio.h>

int main(){
    FILE *f = fopen("test.txt","r");
     if (f==NULL){
        printf("erreur\n");
        return 0;
    }

    char buffer[256];
    char *res = fgets(buffer, 100, f);
    int i = 2;


    while (res!=NULL){
        res = fgets(buffer, i, f);
        if (res!=NULL){
        printf("%s",res);}
        printf(",");
        i++;
    }


    

}