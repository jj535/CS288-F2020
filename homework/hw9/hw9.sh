#!/bin/bash

[[ "$2" -eq "0" ]] && mpicc -o hw9 hw9_point.c || mpicc -o hw9 hw9_scatter.c

mpirun -np 4 ./hw9 $1

