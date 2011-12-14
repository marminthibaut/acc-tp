#!/bin/bash


for i in 10 20 30 40 50 60 70 80 90 100 110 120 130 140 150 160 170 180 190 200
do
  echo -n "$i ";
  cat gprof_r20_s${i}_i100.txt | grep $1 | tac | tail -n 1 | awk '{ print $6 }'
done
