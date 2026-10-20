set terminal png
set output 'mesh_plot.png'
set title "mesh2D"
plot "mesh_to_plot.txt" using 1:2 with lines lt rgb "#d400ff" title "mesh2D"