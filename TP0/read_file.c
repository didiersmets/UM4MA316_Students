#include <stdio.h>

int main(int argc, char *argv[])
{
    if (argc != 2) {
        printf("Usage: %s filename\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");

    if (file == NULL) {
        printf("Cannot open file.\n");
        return 1;
    }

    char line[1000];

    while (fgets(line, sizeof(line), file) != NULL) {
        printf("%s", line);
    }


    fclose(file);

    return 0;
}
