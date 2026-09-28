set title "three sorting algorithms"
set xlabel "N"
set ylabel "time taken"

plot "bubble_sorting.dat" using 1:2 with lines,\
plot "insertion_sorting.dat" using 1:2 with lines,\
plot "merge_sorting.dat" using 1:2 with lines

pause -1
