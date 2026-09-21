set title "Comparaison des temps de calcul des algorithmes de tri"

set xlabel "taille de l'array"
set ylabel "temps de calcul en secondes"

# Échelles logarithmiques
set logscale x
set logscale y

set grid

# Position de la légende
set key top left

plot "plot_co.txt" every ::0::6 using 1:2 \
     with linespoints lw 2 pt 7 lc rgb "red" \
     title "Bubble Sort", \
\
     "plot_co.txt" every ::7::13 using 1:2 \
     with linespoints lw 2 pt 7 lc rgb "blue" \
     title "Insertion Sort", \
\
     "plot_co.txt" every ::14::20 using 1:2 \
     with linespoints lw 2 pt 7 lc rgb "green" \
     title "Merge Sort"

pause -1
