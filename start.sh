#!/bin/sh
make clean && make && ./main.o pos.lst neg.lst pos_t.lst annotations.lst
for i in pruebas/*.mat; do
	    python statsValue.py $i
done