# What: fft in python
# Usage: python fft.py
#   data = [1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0]
#   fft(data) = [(4+0j), (1-2.414j), 0j, (1-0.4142j), 0j, (1,+0.4142j), 0j, (1+2.4142j)]
 
from cmath import exp, pi
 
def fft(x, sign = 1):
    N = len(x)
    if N <= 1: return x
    even = fft(x[0::2], sign)
    odd =  fft(x[1::2], sign)
    return [even[k] + exp(-2j*pi*k*sign/N)*odd[k] for k in xrange(N/2)] + \
           [even[k] - exp(-2j*pi*k*sign/N)*odd[k] for k in xrange(N/2)]

def ifft(x):
  y = fft(x, -1)
  N = len(x)
  return [y[k]/N for k in xrange(N)]

data = [1.0, 2.0, 5.0, 7.0, 9.0, 0.0, 0.0, 0.0]
print "data=",data
y = fft(data)
print "fft(data)=",y
print "ifft(fft(data))=",ifft(y)
