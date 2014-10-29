#!/usr/bin/env python

import sys
import numpy as np
import math

A = np.matrix("1 2 3; 4 5 6; 7 8 9")

B = np.matrix("2 2 2; 2 2 2; 2 2 2")


print np.multiply(A,B)


