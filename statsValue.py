#!/usr/bin/env python

import sys
import numpy as np


filename = sys.argv[1]

print filename

Z = np.loadtxt(filename)

def  inverted_gaussian_filter(Z,A=1,sx=1,sy=1):
    
    h,w = np.shape(Z)

    x = range(w)
    y = range(h)

    xo = w/2
    yo = h/2

    X,Y = np.meshgrid(x,y)

    F = A*np.exp(-(X-xo)**2/(2.*sx**2)-(Y-yo)**2/(2.*sy**2))
    
    return np.sum((1-F)*Z)

def  inverted_exponential_filter(Z,L=1):
    
    h,w = np.shape(Z)

    x = range(w)
    y = range(h)

    xo = w/2
    yo = h/2

    X,Y = np.meshgrid(x,y)

    F = L**2*np.exp(-abs(X-xo)*L)*np.exp(-abs(Y-yo)*L);
    
    return np.sum((1-F)*Z)

#Here is the business:
def image_statistics(Z):
    #Input: Z, a 2D array, hopefully containing some sort of peak
    #Output: cx,cy,sx,sy,skx,sky,kx,ky
    #cx and cy are the coordinates of the centroid
    #sx and sy are the stardard deviation in the x and y directions
    #skx and sky are the skewness in the x and y directions
    #kx and ky are the Kurtosis in the x and y directions
    #Note: this is not the excess kurtosis. For a normal distribution
    #you expect the kurtosis will be 3.0. Just subtract 3 to get the
    #excess kurtosis.
    import numpy as np

    h,w = np.shape(Z)

    x = range(w)
    y = range(h)


    #calculate projections along the x and y axes
    yp = np.sum(Z,axis=1)
    xp = np.sum(Z,axis=0)

    #centroid
    cx = np.sum(x*xp)/np.sum(xp)
    cy = np.sum(y*yp)/np.sum(yp)

    #standard deviation
    x2 = (x-cx)**2
    y2 = (y-cy)**2

    sx = np.sqrt( np.sum(x2*xp)/np.sum(xp) )
    sy = np.sqrt( np.sum(y2*yp)/np.sum(yp) )

    #skewness
    x3 = (x-cx)**3
    y3 = (y-cy)**3

    skx = np.sum(xp*x3)/(np.sum(xp) * sx**3)
    sky = np.sum(yp*y3)/(np.sum(yp) * sy**3)

    #Kurtosis
    x4 = (x-cx)**4
    y4 = (y-cy)**4
    kx = np.sum(xp*x4)/(np.sum(xp) * sx**4)
    ky = np.sum(yp*y4)/(np.sum(yp) * sy**4)


    return cx,cy,sx,sy,skx,sky,kx,ky

#We can check that the result is the same if we use the full 2D data array
def image_statistics_2D(Z):
    h,w = np.shape(Z)

    x = range(w)
    y = range(h)

    X,Y = np.meshgrid(x,y)

    #Centroid (mean)
    cx = np.sum(Z*X)/np.sum(Z)
    cy = np.sum(Z*Y)/np.sum(Z)

    ###Standard deviation
    x2 = (range(w) - cx)**2
    y2 = (range(h) - cy)**2

    X2,Y2 = np.meshgrid(x2,y2)

    #Find the variance
    vx = np.sum(Z*X2)/np.sum(Z)
    vy = np.sum(Z*Y2)/np.sum(Z)

    #SD is the sqrt of the variance
    sx,sy = np.sqrt(vx),np.sqrt(vy)

    ###Skewness
    x3 = (range(w) - cx)**3
    y3 = (range(h) - cy)**3

    X3,Y3 = np.meshgrid(x3,y3)

    #Find the thid central moment
    m3x = np.sum(Z*X3)/np.sum(Z)
    m3y = np.sum(Z*Y3)/np.sum(Z)

    #Skewness is the third central moment divided by SD cubed
    skx = m3x/sx**3
    sky = m3y/sy**3

    ###Kurtosis
    x4 = (range(w) - cx)**4
    y4 = (range(h) - cy)**4

    X4,Y4 = np.meshgrid(x4,y4)

    #Find the fourth central moment
    m4x = np.sum(Z*X4)/np.sum(Z)
    m4y = np.sum(Z*Y4)/np.sum(Z)

    #Kurtosis is the fourth central moment divided by SD to the fourth power
    kx = m4x/sx**4
    ky = m4y/sy**4

    return cx,cy,sx,sy,skx,sky,kx,ky



#Calculate the image statistics using the projection method
stats_pr = image_statistics(Z)

cx,cy,sx,sy,skx,sky,kx,ky = image_statistics(Z)

inv_g = inverted_gaussian_filter(Z,A=1,sx=sx,sy=sy)
inv_e = inverted_exponential_filter(Z)

#Confirm that they are the same by using a 2D calculation
stats_2d = image_statistics_2D(Z)

names = ('Centroid x','Centroid y','StdDev x','StdDev y','Skewness x','Skewness y','Kurtosis x','Kurtosis y')

print 'Statistis\t1D\t2D'
for name,i1,i2 in zip(names, stats_2d,stats_pr):
    print '%s \t%.2f \t%.2f'%(name, i1,i2)

print 'Sensibilidad Inv G:\t%.5f'%(inv_g)
print 'Sensibilidad Ing E:\t%.5f'%(inv_e)