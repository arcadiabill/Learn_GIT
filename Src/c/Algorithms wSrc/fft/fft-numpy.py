#!python2.5
# What: fft in python using numpy.

from numpy.fft import fft
from numpy.fft import ifft
from numpy import array

from numpy import set_printoptions, get_printoptions
# print get_printoptions()
set_printoptions(precision = 4)
set_printoptions(suppress=True)

a = array((0, 1, 7, 2, -1, 3, 7, 8, 0, -23, -7, 31, 1, 31, -7, -31))

print "data =", a
y = fft(a)
print "fft(data) = ", y
z = ifft(y)
print "ifft(fft(data)) = ", z

