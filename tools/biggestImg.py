#!/usr/bin/env python

import sys
import numpy as np
import scipy
from scipy import misc


fileNameList = sys.argv[1]
fileList = open(fileNameList, "r")

maxH = 0
maxW = 0
minH = 90000
minW = 90000
count = 0
sumw = 0
sumh = 0

for fileName in fileList:	

	Z = misc.imread(fileName.rstrip('\n'))
	h, w , c = Z.shape
	if h>maxH:
		maxH = h
	if w>maxW:
		maxW = w
	if h<minH:
		minH = h
	if w<minW:
		minW = w
	sumw += w
	sumh += h
	count += 1


print 'Max: (%4d, %4d)'%(maxW,maxH)
print 'Min: (%4d, %4d)'%(minW,minH)
print 'Mean:(%4d, %4d)'%(sumw/count,sumh/count)