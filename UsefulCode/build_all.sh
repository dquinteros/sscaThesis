#!/bin/sh
if [[ $# > 0 ]] ; then
	base=`basename $1 .c`
	echo "compiling $base"
	gcc -ggdb `pkg-config opencv --cflags --libs` $base.c -o $base 
else
	for i in *.c; do
	    echo "compiling $i"
	    gcc -ggdb `pkg-config --cflags opencv` -o `basename $i .c`.o $i `pkg-config --libs opencv`;
	done
	for i in *.cpp; do
	    echo "compiling $i"
	    g++ -std=c++11 -ggdb `pkg-config --cflags opencv` -o `basename $i .cpp`.o $i `pkg-config --libs opencv`;
	done 
	for i in *.cc; do
	    echo "compiling $i"
	    g++ -std=c++11 -ggdb `pkg-config --cflags opencv` -o `basename $i .cc`.o $i `pkg-config --libs opencv`;
	done 
	rm -rf 0
fi
