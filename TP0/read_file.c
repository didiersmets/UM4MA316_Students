#include <stdio.h>

int main(int argc, char *argv[])
{
    if (argc != 2) {
        printf("Usage: %s filename\n", argv[0]);
        return 1;
    }

    FILE *f = fopen(argv[1], "r");

    if (f == NULL) {
        printf("Cannot open file: %s\n", argv[1]);
        return 1;
    }

    char line[256];

    while (fgets(line, sizeof(line), f) != NULL) {
        printf("%s", line);
    }

    fclose(f);

    return 0;
}
