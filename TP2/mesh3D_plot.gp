set terminal pngcairo size 1000,700
set output "mesh3D.png"

set title "3D Mesh"
set xlabel "x"
set ylabel "y"
set zlabel "z"

set grid

splot "mesh3D.txt" using 1:2:3 with lines title "mesh"

set output