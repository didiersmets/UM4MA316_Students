#include <stdio.h> // pour printf
#include <stdlib.h> // pour atoi
int main(int argc, char **argv)
{
    char *nom = argv[1];
    int age = atoi(argv[2]);
    printf("Vous m'avez entré %d arguments\n", argc);
    printf("Hello %s, l'an prochain tu auras %d ans !\n", nom, age + 1);
    return 0;
}