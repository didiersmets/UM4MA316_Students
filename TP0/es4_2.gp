set terminal png
set output 'x_sinx.png'
set title "f(x) = sin(x) / x"
set xlabel "x"
set ylabel "f(x)"
set xrange [-6*pi:6*pi]
plot sin(x) / x
