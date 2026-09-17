set title "f(x) = sin(x)/x"
set xlabel "x"
set ylabel "sin(x)/x"
set grid

plot "computed_list.txt" using 1:2 with lines title "sin(x)/x"

pause -1

