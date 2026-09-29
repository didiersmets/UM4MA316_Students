

set title "three sorting algorithms"
set xlabel "N"
set ylabel "time taken"

set logscale x
set logscale y

plot "bubble_sorting.dat" using 1:2 with lines,\
     "insertion_sorting.dat" using 1:2 with lines,\
     "merge_sorting.dat" using 1:2 with lines

pause -1
