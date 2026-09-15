#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "../include/circular_buffer_queue.h"




int main(int argc, char *argv[]){

    struct Queue *q = queue_init(sizeof(int),0);

    srand(time(NULL));
    int p;
    int l_max = 0;
    int N;
    argc<2 ? printf("Veuillez entrer un entier :\n"), scanf("%d",&N) : (N = atoi(argv[1]));

    for(int i=0; i<N; i++){
        p = rand()%11;
        printf("tour %d p=%d\n",i+1,p);
        
        if ( p%2 == 1 ){

            printf("p=%d entre dans la queue\n",p);
            queue_enqueue(q,&p);

            if (q->length>l_max){
                l_max=q->length;
            }

        } else {

            if (q->length==0){
                printf("p=%d ne fait rien, file vide\n",p);
            } else {
                void *dest=malloc(sizeof(q->elem_size));
                queue_dequeue(q, dest);
                int QuiEstCe = *(int *)dest;
                printf("%d est sorti de la queue\n", QuiEstCe);
                free(dest);
            }
        }
    }
    printf("l_max = %d\n", l_max);



    //affiche le contenu de la queue
    int taille = 0;
    char *adresse_valeur;

    while(taille < q->length){

        adresse_valeur = (char *)q->data +   q->elem_size * (( q->front + taille ) % q->capacity);
        
        //remarque, ajouter 1 à char* incrémente l'adresse de 1 octet, mais si je cast en int*, alors ça incrémente de 4 octets
        printf("Position %d : %d\n", taille + 1, *(int*) adresse_valeur);
        
        taille++;
    }

    queue_dispose(q);

    return 0;   
}