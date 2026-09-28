set title "Maximum queue length"
set xlabel "n"
set ylabel "l_max"

set logscale x
set logscale y
set grid

plot "lmax.dat" using 1:2 with linespoints title "experiment", \
     sqrt(x) with lines title "sqrt(n)"

pause -1