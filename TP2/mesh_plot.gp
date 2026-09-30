set terminal pngcairo size 1000,700
set output "mesh.png"

set title "2D mesh"
set xlabel "x"
set ylabel "y"

set grid

plot "mesh.txt" using 1:2 with lines title "mesh"

set output