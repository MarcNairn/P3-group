#!/bin/gnuplot -persist

# 
set title "Cylinder between parallel plates" 
set xlabel "XAXIS"
set ylabel "YAXIS"
set cblabel "Voltage"

#set xrange[15:25]
#set yrange[15:25]

set cbrange[-100:100]
set palette defined (0 "grey", 1 'blue', 2 'green', 3 'red', 4 'black', 5 'pink', 6 'yellow', 7 'brown', 8 'orange', 9 'white')


set terminal postscript eps enhanced color  # colour for map
set output "plates.ps" # output file
set pm3d map at b # put heat map at bottom of graph

set size ratio -1
set contour
set cntrparam levels discrete -100, -75, -50, -25, 0, 25, 50, 75, 100



splot 'laplace.dat'
