#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

void timer_start(struct timeval *tv){ gettimeofday(tv,NULL);}

unsigned int timer_stop(const struct timeval *tv, const char *str){
    struct timeval now;
    gettimeofday(&now,NULL);
    unsigned int mus = 1000000 * (now.tv_sec - tv->tv_sec);
    mus += (now.tv_usec - tv->tv_usec); //ajoutes les microsecondes 
    if (str[0]){
        printf("Temps %s : ", str);
        if (mus >= 100000){
            printf("%.3f s\n", (float)mus/ 1000000);
        } else {
            printf("%.3f ms\n", (float)mus/ 1000);
        }
    }
    return (mus);
}


float timer_stop2(const struct timeval *tv){
    struct timeval now;
    gettimeofday(&now,NULL);
    float mus = (now.tv_sec - tv->tv_sec)*1000000;
    mus += (now.tv_usec - tv->tv_usec);
    return mus/1000; //en milliseconde
}

void Bubble_sort(int* a, int N){
    if (N<2) return;
    int temp;
    for(int j=N-1; j>0; j--){
        for(int i=0; i<j; i++){
            if (a[i]>a[i+1]){
                temp = a[i+1];
                a[i+1] = a[i];
                a[i] = temp;
            }
        }
    }
}

void Insertion_sort(int* a, int N){
    if (N<2) return;
    int temp;
    for(int i = 1; i<N ; i++){
        while(a[i]<a[i-1]){
            temp=a[i-1];
            a[i-1]=a[i];
            a[i]=temp;
            i--;
            if (i<1) break; //je ne veux pas que le while test a[-1]
        }
    }
}



void Merge(int *T, int p, int q, int r){



    int taille1 = q - p+1; //nb d'elements entre  T[p] et T[q] car merge(T,p,q)
    int taille2 = r - q; //nb d'elements entre  T[q+1] et T[r] car merge(T,q+1,r)



    int *tableau = malloc(sizeof(int)*(taille1+taille2));

    int i=0;
    int j = 0;
    int count = 0;

    while(i<taille1 && j<taille2){
        if (T[p+i]<=T[q+1+j]){
            tableau[count++]=T[p+i];
            i++;
        } else {
            tableau[count++]=T[q+1+j];
            j++;
        }
    }

    while (i<taille1){
        tableau[count++]=T[p+i];
        i++;
    }

    while (j<taille2){
        tableau[count++]=T[q+j+1];
        j++;
    }

    for(int k=p; k<(p+(taille1+taille2)); k++){
        T[k]=tableau[k-p];

    }

    free(tableau);
}

void MergeSort(int *T, int p, int r){
    if (p<r){
        int q = (int) (p+r)/2;
        MergeSort(T,p,q);
        MergeSort(T,q+1,r);
        Merge(T,p,q,r);
    }
}


int main(int argc, char* argv[]){
    struct timeval chrono;
    srand(time(NULL));

    int N;
    argc<2 ? printf("Afin de tester la validite de nos fonctions, veuillez entrer un entier\n"), scanf("%d",&N) : (N=atoi(argv[1]));

    int *array = (int *)malloc(sizeof(int)*N);
    int *array2 = (int *)malloc(sizeof(int)*N);
    int *array3 = (int *)malloc(sizeof(int)*N);

    printf("\nTableau de base : ["); //affiche le contenu du tableau en création (j'en crée plusieurs comme demandé dans l'exercice)
    for(int i=0; i<N-1; i++){
        array[i]=rand()%(N+1); //nombre aléatoire entre 0 et la taille du tableau car pourquoi pas
        array2[i]=array[i];
        array3[i]=array[i];
        printf("%d,", array[i]);
    }
    array[N-1]=rand()%(N+1);
    array2[N-1]=array[N-1];
    array3[N-1]=array[N-1];
    printf("%d]\n\n",array[N-1]);

    timer_start(&chrono);
    Bubble_sort(array,N);
    timer_stop(&chrono, "du bubble sort");


    printf("Bubble sort : [");
    for(int i=0; i<N-1; i++){
        printf("%d,",array[i]);
    }
    printf("%d]\n\n", array[N-1]);


    timer_start(&chrono);
    Insertion_sort(array2,N);
    timer_stop(&chrono, "du insertion sort");

    printf("Insertion sort : [");
    for(int i=0; i<N-1; i++){
        printf("%d,",array2[i]);
    }
    printf("%d]\n\n", array2[N-1]);

    timer_start(&chrono);
    MergeSort(array3,0,N-1);
    timer_stop(&chrono, "du merge sort");

    printf("Merge sort : [");
    for(int i=0; i<N-1; i++){
        printf("%d,",array3[i]);
    }
    printf("%d]\n\n\n", array3[N-1]);

    int LesTableauxSontégaux = 1;

    for(int i=0; i<N; i++){
        if ((array[i]!=array2[i]) || (array[i]!=array3[i])){
            LesTableauxSontégaux = 0;
            break;
        }
    }

    LesTableauxSontégaux==1 ? printf("Les tableaux sont egaux\n") : printf("Les tableaux sont pas égaux\n");

    free(array);
    free(array2);
    free(array3);


    //partie GNUPLOT

    FILE *f = fopen("valeurs","w");

    if (f==NULL){
        printf("fichier txt non ouvert");
        exit(1);
    } 

    int taille_tableau[7]={10,20,50,100,200,500,1000};
    int *array_pour_bubble_sort;
    int *array_pour_insertion_sort;
    int *array_pour_merge_sort;
    float temps[3];
    int val;

    for(int i=0; i<7;i++){

        array_pour_bubble_sort = (int*) malloc(sizeof(int)*taille_tableau[i]); //cast facultatif mais ça me rappelle que le type de retour du malloc est void*
        array_pour_insertion_sort = (int*) malloc(sizeof(int)*taille_tableau[i]);
        array_pour_merge_sort = (int*) malloc(sizeof(int)*taille_tableau[i]);


        for(int j=0; j<taille_tableau[i];j++){ //création des tableaux à ranger de taille taille_tableau[i]

            val = rand()%(taille_tableau[i]+1);  //des valeurs entre 0 et taille_tableau[i] inclus
            array_pour_bubble_sort[j] = val;
            array_pour_insertion_sort[j]= val;
            array_pour_merge_sort[j]= val;
        }

        //Je mesure le temps que prend la fonction à organiser ce tableau

        timer_start(&chrono);
        Bubble_sort(array_pour_bubble_sort,taille_tableau[i]);
        temps[0]=timer_stop2(&chrono);

        timer_start(&chrono);
        Insertion_sort(array_pour_insertion_sort,taille_tableau[i]);
        temps[1]=timer_stop2(&chrono);

        timer_start(&chrono);
        MergeSort(array_pour_merge_sort,0,taille_tableau[i]-1);
        temps[2]=timer_stop2(&chrono);

        //j'écris dans le fichier les valeurs trouvés, créant les axes des graphs à dessiner
        fprintf(f,"%d %f %f %f\n", taille_tableau[i], temps[0], temps[1], temps[2]);


        free(array_pour_bubble_sort);
        free(array_pour_insertion_sort);
        free(array_pour_merge_sort);
    }

    fclose(f);

    system(
        "gnuplot -persist -e \""
        "set logscale x;" 
        "set logscale y;"
        "set ylabel 'Temps (ms)';"
        "set xlabel 'Taille du tableau a organiser';"
        "set title 'Comparaison des trois algos';"
        "plot 'valeurs' using 1:2 with linespoints title 'Bubble sort'," 
        "'valeurs' using 1:3 with linespoints title 'Insertion sort', "
        "'valeurs' using 1:4 with linespoints title 'Merge sort'"
        "\""
        );
    


    return 0;
}