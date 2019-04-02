#!/usr/bin/gnuplot -p

plot "test.dat" using 2:3 title ""
set xlabel "prey population"
set ylabel "predator population"
set title "phys3071 as04 melsom 4259324"
set yrange [0:50]
set term postscript color
set output "as04-plot2-melsom-42593249.ps"
replot

plot "test.dat" using 1:3 title "predator", "test.dat" using 1:2 title "prey"
set xlabel "time"
set ylabel "population"
set title "phys3071 as04 melsom 4259324"
set yrange [0:85]
set term postscript color
set output "as04-plot1-melsom-42593249.ps"
replot
