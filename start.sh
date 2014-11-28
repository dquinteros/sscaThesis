#!/bin/sh
rm master.zip
wget https://github.com/dquinteros/sscaThesis/archive/master.zip
unzip -u master.zip
cd sscaThesis-master
make clean && make
screen -d -m ./main.o -p list_files/pos_files.lst -n list_files/neg_files.lst -c svm -t list_files/tfa.lst
screen -d -m ./main.o -p list_files/pos_files.lst -n list_files/neg_files.lst -c svm -t list_files/tfb.lst
screen -d -m ./main.o -p list_files/pos_files.lst -n list_files/neg_files.lst -c svm -t list_files/tfc.lst
screen -d -m ./main.o -p list_files/pos_files.lst -n list_files/neg_files.lst -c svm -t list_files/tfd.lst
screen -d -m ./main.o -p list_files/pos_files.lst -n list_files/neg_files.lst -c svm -t list_files/tfe.lst
screen -d -m ./main.o -p list_files/pos_files.lst -n list_files/neg_files.lst -c svm -t list_files/tff.lst
screen -d -m ./main.o -p list_files/pos_files.lst -n list_files/neg_files.lst -c svm -t list_files/tfg.lst
screen -d -m ./main.o -p list_files/pos_files.lst -n list_files/neg_files.lst -c svm -t list_files/tfh.lst

