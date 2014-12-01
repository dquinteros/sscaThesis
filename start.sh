#!/bin/sh
#rm master.zip
#wget https://github.com/dquinteros/sscaThesis/archive/master.zip
#unzip -u master.zip
#cd sscaThesis-master
make clean && make
./main.o -p list_files/pos_files.lst -n list_files/neg_files.lst -c boost -t list_files/test_files.lst
