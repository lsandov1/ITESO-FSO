#!/usr/bin/env gnuplot

set term png
set output 'sqrt.png'
plot [0:1] sqrt(1-x*x) title 'y=sqrt(1-x^2)'

set output 'trapezium.png'
set title 'Numeric approximation of PI'
set xlabel '# of trapeziums'
set ylabel ''

set logscale x 10
set logscale y
plot 'pi_pthread.data' using 1:2 w lines title 'Trapezium Method', \
     'pi_pthread.data' using 1:3 w lines title 'Constant PI'

set term x11