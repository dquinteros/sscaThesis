#!/usr/bin/env python

import sys
import numpy as np
import math


filename = sys.argv[1]

print filename

Z = np.loadtxt(filename)

h,w = np.shape(Z)

x = range(w)
y = range(h)

X,Y = np.meshgrid(x,y)

xo = w/2
yo = h/2

F = ((X-xo)**2+(Y-yo)**2)**(.5)

print F

np.savetxt('test.out', F, delimiter=' ')