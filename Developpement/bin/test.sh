#!/bin/bash

for i in $* 
do
  for j in 100 200 300 400 500 600 700 800 1000 2000 3000 4000 5000 6000 7000 8000 9000 10000 
  do
    echo $j/$i
    ./test $j $i 10
    gprof test > gprof_$j_$i.txt
  done
done
