set terminal pngcairo size 1000,700
set output "function.png"

set title "sin(x)/x" 
plot [-6*pi:6*pi] sin(x)/x

set output