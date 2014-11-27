#!/bin/sh
rm master.zip
wget https://github.com/dquinteros/sscaThesis/archive/master.zip
unzip -u master.zip
cd sscaThesis-master
make clean && make
screen -d -m ./main.o -p list_files/train_pos_list_files.lst -n list_files/train_neg_list_files.lst -c svm -t list_files/test_pos_list_files_1.lst
screen -d -m ./main.o -p list_files/train_pos_list_files.lst -n list_files/train_neg_list_files.lst -c svm -t list_files/test_pos_list_files_2.lst
screen -d -m ./main.o -p list_files/train_pos_list_files.lst -n list_files/train_neg_list_files.lst -c svm -t list_files/test_pos_list_files_3.lst
screen -d -m ./main.o -p list_files/train_pos_list_files.lst -n list_files/train_neg_list_files.lst -c svm -t list_files/test_pos_list_files_4.lst
screen -d -m ./main.o -p list_files/train_pos_list_files.lst -n list_files/train_neg_list_files.lst -c svm -t list_files/test_pos_list_files_5.lst
screen -d -m ./main.o -p list_files/train_pos_list_files.lst -n list_files/train_neg_list_files.lst -c svm -t list_files/test_pos_list_files_6.lst
screen -d -m ./main.o -p list_files/train_pos_list_files.lst -n list_files/train_neg_list_files.lst -c svm -t list_files/test_pos_list_files_7.lst
screen -d -m ./main.o -p list_files/train_pos_list_files.lst -n list_files/train_neg_list_files.lst -c svm -t list_files/test_pos_list_files_8.lst

#for i in pruebas/*.mat; do
#	    python pysrc/statsValue.py $i
#donein