set terminal png
set output 'x_sinx_x_graph.png'
set title "x->sin(x)/x plot"
set xrange [-6*pi:6*pi]
plot "series.txt" with lines
