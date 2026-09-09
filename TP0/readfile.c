#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

    FILE *file = fopen(argv[1], "r");

    if (file == NULL) {
        printf("Could not open file\n");
        return 1;
    }

    char line[256];
    
    while (fgets(line, 256, file) != NULL) {
        printf("%s", line);
    }

    fclose(file);

    return 0;
}