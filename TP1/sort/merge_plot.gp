set terminal png
set output 'merge_plot.png'
set title "merge algos time comparison"
set logscale xy 10
plot "bubble_exec_times.txt" with lines lt rgb "#ff0000" title "bubble", \
    "insertion_exec_times.txt" with lines lt rgb "#ffea00" title "insertion", \
    "merge_exec_times.txt" with lines lt rgb "#09ff00" title "merge", \
    "merge_noalloc_exec_times.txt" with lines lt rgb "#0000ff" title "merge noalloc", \
    "merge_pingpong_exec_times.txt" with lines lt rgb "#f700ff" title "merge pingpong"