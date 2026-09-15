
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE *fptr;
    char filename[256];
    char memory[1000];

    
    printf("Enter filename: ");
    if (fgets(filename, sizeof(filename), stdin) == NULL) {
        return 1;
    }

    filename[strcspn(filename, "\n")] = '\0';

 
    fptr = fopen(filename, "r");

   
    if (fptr == NULL) {
        printf("Error: Could not open file.\n");
        return 1;
    }

    while (fgets(memory, sizeof(memory), fptr)) {
        printf("%s", memory);
    }

    fclose(fptr);
    return 0;
}