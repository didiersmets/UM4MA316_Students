#include <stdio.h>


int main(){
    // \n est il un caractère? il peut, mais il peut être int aussi
    //diff entre res et buff : même contenu, différents objets

    int compteur = 0;
    FILE* f = fopen("test2.txt","r");

    char buffer[256];
    char *res;
    printf("taille de res avant fgets : %ld\n", sizeof(res));
    res = fgets(buffer, 100, f);
    printf("%s",res); printf("%s",buffer);
    printf("taille de long unsigned int : %ld\n", sizeof(long unsigned int));
    printf("taille de res : %ld\n", sizeof(res));
    printf("taille de res : %ld\n", sizeof(buffer));
    res = fgets(buffer, 100, f);

    printf("%s",res);

    printf("taille de res  : %ld\n", sizeof(res));
    printf("%s",buffer);
    res = fgets(buffer, 100, f);
     printf("%s",res);
    printf("%s",buffer);

    char m[3] = {'\0'};
    char n = {'\n'};
    printf("%s\n",m);


    printf("tailleazezaeza de m %ld\n",sizeof(m));
     printf("tailleazezaeza de n %ld\n",sizeof(n));
    printf("tailleazezaeza du truc  %ld\n",sizeof('\0')); //pk 4 et pas 1 
    printf("tailleazezaeza du truc  %ld\n",sizeof('\n'));
    printf("tailleazezaeza du truc  %ld\n",sizeof('o'));
}