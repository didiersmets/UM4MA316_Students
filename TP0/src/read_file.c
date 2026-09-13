#include <stdio.h>


int main(int argc, char *argv[]) {

    if (argc!=2){
        fprintf(stderr, "%s <file path>\n", argv[0]);
        return 1;
    }
    FILE* fp;
    fp = fopen(argv[1], "r");
    size_t n = 1024;
    char buff[n];
    char *c;

    while ((c=fgets(buff, n,fp)) != NULL) {
        printf("%s", c);
    }

    fclose(fp);
}
