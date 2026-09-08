set terminal png
set output 'x_sinx_x_graph.png'
set title "x->sin(x)/x plot"
plot "series.txt" with lines
