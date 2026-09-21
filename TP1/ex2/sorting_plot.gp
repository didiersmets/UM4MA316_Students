set terminal pngcairo size 1000,700
set output "times.png"

set title "Sorting algorithms execution time"
set xlabel "N"
set ylabel "Execution time (s)"

set logscale x
set logscale y

set grid

plot "times.txt" using 1:2 with linespoints title "Bubble sort", \
     "times.txt" using 1:3 with linespoints title "Insertion sort", \
     "times.txt" using 1:4 with linespoints title "Merge sort", \
     "times.txt" using 1:5 with linespoints title "Merge v2 sort"

set output