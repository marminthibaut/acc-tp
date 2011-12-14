#!/bin/bash


for i in 100 200 300 400 500 600 700 800 900 1000
do
  echo -n "$i ";
  cat gprof_r${2}_s${i}_i${3}.txt | grep $1 | tac | tail -n 1 | awk '{ print $6 }'
done
