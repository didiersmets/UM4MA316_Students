#include <stdio.h>

//first argument is filename
int main(int argc, char *argv[]){

    FILE *fptr;
    fptr = fopen(argv[1], "r"); 
    char row[256];

    while (fgets(row,256,fptr)){
        printf("%s", row);
    }

    return 0;
}