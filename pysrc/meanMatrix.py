#!/usr/bin/env python

import sys
import numpy as np


filename_list = sys.argv[1]

print filename_list

lst = open(filename_list, "r+")

line = lst.readline()
Z = np.empty(shape=[122,58])
count = 0
while line:
	print line
	Z += np.loadtxt(line.rstrip('\n'));
	count = count+1
	line = lst.readline()
  
F = Z/count

np.savetxt("BOOST_Result_32_64.mat",F)