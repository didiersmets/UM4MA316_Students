#include <stdio.h>


int main() {

    char *riga;
    size_t len = 0;

    while(getline(&riga, &len, stdin) != -1) {
        printf("%s", riga);
    }

    

    return 0;
}