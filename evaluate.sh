#!/bin/sh
if [ $# -le 0 ]; then	
	make clean && make && ./main.o
	for i in pruebas/*.mat; do
	    python statsValue.py $i
	done
else 
	for i in $1/*.out; do
	    python statsValue.py $i
	done
fi
