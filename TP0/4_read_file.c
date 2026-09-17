#include <stdio.h>

#define MAX_LINE_SIZE 1000

int main(int argc, char *argv[]){

    FILE *fp = fopen(argv[1], "r");
    if(fp == NULL){
        perror("failed to open file\n");
        return 1;
    }


    char line[MAX_LINE_SIZE];

    while(fgets(line, sizeof(line), fp)){
        printf("%s", line);
    }

    fclose(fp);

    return 0;
}