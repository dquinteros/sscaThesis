#!/bin/sh
make clean && make && ./main.o list_files/pos.lst list_files/neg.lst list_files/pos_normalized_64_128.lst
#for i in pruebas/*.mat; do
#	    python pysrc/statsValue.py $i
#done