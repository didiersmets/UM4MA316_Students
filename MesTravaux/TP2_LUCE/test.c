#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int main(){

    FILE *f = fopen("valeurs","w");
    fprintf(f, "1 2 2\n");
    fprintf(f, "2 3 4\n");
    fprintf(f, "2 4 5\n");
    fprintf(f, "3 5 6\n");
    fprintf(f, "4 7 7\n");
    
    fclose(f);
    char buffer[1000];
    int nb=0;
  
     nb += snprintf(buffer, sizeof(buffer), "gnuplot -persist -e \""
        "set xrange [0:10];"
        "set yrange [0:10];"
        "set ylabel 'y';"
        "set xlabel 'x';"); 

    nb += snprintf(buffer+nb, sizeof(buffer)-nb,"plot '%s' every ::0::2 using 1:2 with linespoints title 'yayaya',","valeurs");

    nb += snprintf(buffer+nb, sizeof(buffer)-nb,"'%s' every ::3::4 using 1:2 with linespoints title 'yoyoyo';","valeurs");

    nb += snprintf(buffer+nb, sizeof(buffer)-nb,"\"");

    
    system(buffer);
    
}