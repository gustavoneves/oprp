#!/bin/bash
for i in {1..10};
do
	for j in 1 2 4 8;
 	do
   		for k in 500 750 1000 1250 1500 1750 2000 4000;
	        do
		  ./pthreads_matrix_mult $j $k > "$j"_"$k"-"$i"
	 	done;
        done;
done
