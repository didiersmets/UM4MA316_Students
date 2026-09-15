#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{

    FILE * f = fopen ("test-tp0.txt" , "r");
    
    if (!f) {
        perror ("Error opening file");
        return -1;
    }
     
    char line[128];
    while (fgets(line, 128, f) != NULL ) {
      printf("%s", line);
    }

    fclose (f); 
    
    return 0;
}


