#!/bin/sh
make clean && make && ./main
for i in pruebas/*.mat; do
	    python statsValue.py $i
done