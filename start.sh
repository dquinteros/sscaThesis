#!/bin/sh
make clean && make && ./main.o pos.lst
for i in pruebas/*.mat; do
	    python statsValue.py $i
done