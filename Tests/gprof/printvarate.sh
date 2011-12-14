#!/bin/bash


for i in  20 40 50 60 80 100
do
  echo -n "$i ";
  cat gprof_r${i}_s${2}_i${3}.txt | grep $1 | tac | tail -n 1 | awk '{ print $6 }'
done
