#!/bin/gnuplot -persist


set title "Cylinder between parallel plates"
set xlabel "XAXIS"
set ylabel "YAXIS"
set terminal postscript eps enhanced color
set output "plates3.ps"
set view map 
set pm3d map at b


splot 'laplace.dat'
