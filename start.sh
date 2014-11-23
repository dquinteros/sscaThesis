#!/bin/sh
make clean && make && ./main.o -p list_files/train_pos_list_files.lst -n list_files/train_neg_list_files.lst -c svm -t list_files/test_pos_list_files.lst
#for i in pruebas/*.mat; do
#	    python pysrc/statsValue.py $i
#donein