#!/bin/sh

for mass in 15 40 55
do
	for life in 1 10 100 1000
	do
		cd 2201_sig_mytag_${mass}_${life}/
		mv output_*/*.root .
		hadd sig_mytag_${mass}_${life}.root *.root
		mv sig_mytag_${mass}_${life}.root ../sig_files_mytaggers
		cd ..
	done
done
