#!python2.5

# python2.5: eea(5,7)= [1, 3, -2]
# python3:   syntax error: while v2[0]<>0:
# python2.7: syntax error: def crt(ms,as):

'''
  From Kirby Urner pdx4d@teleport.com
  Date Tue, 28 Aug 2001 09:57:54 -0700

  Here's a version of the Extended Euclidean Algorithm, with
  related inverse and Chinese Remainder Theorem functions.

EEA:
  The EEA returns a 3-tuple, the 0th element being the gcd(a,b),
  the next two being s,t such that gcd(a,b) = s*a + t*b, i.e.
  two integers which bring the initial a,b within the gcd of
  one another.

  Examples:
    >>> eea(a,b)              # gcd(a,b) = 1
    [g, x, y], where: a * x + b * y = g
    >>> eea(17,25)            # gcd(a,b) = 1
    [1, 3, -2]
    >>> 3*17 - 2*25           # s = 3, t = -2
    1
    >>> eea(29834,8282)       # gcd(a,b) = 2
    [2, -88, 317]
    >>> -88*29834 + 317*8282  # s = -88, t = 317
    2

Inverse:
  With EEA, you can also find the inverse of xx mod nn, provided
  gcd(xx,nn)=1. The inverse is that number which, multiplying
  xx, gives a remainder of 1 when divided by nn.

    inverse(xx,nn) = eaa(xx,nn)[2]
    >>> eea(xx,nn)              # gcd(xx,nn) = 1
      [g, xinv, y], where: xx * xinv + nn * y = 1

  Example: 
      >>> inverse(7,4) # find xinv such that (xinv * 7) mod 4 = 1.
      3

  i.e. (3*7) mod 4 = 21 mod 4 = 1 = integer remainder of 21/4.

CRT:
  The Chinese Remainder Theorem states that if I give you
  a smattering of divisors, all coprime to each other, and
  tell you what the remainders for each of them is, then
  you can tell me a unique number which meets my specifications.

  Example:  Your divisors are 7,11 and 15.  The respective
  remainders are 2, 3 and 0.  What is a number that works?

  Computing:
      >>> crt([7,11,15],[2,3,0])
      135
  Check:
      >>> 135 % 7
      2
      >>> 135 % 11
      3
      >>> 135 % 15
      0
  So 135 Works.

Uses of CRT:
  The also EEA comes up in CS in connection with RSA.  You
  need it to find secret pair d, matched with e, such that
  (d*e) mod (p-1)(q-1) = 1, where p,q are the two humongous
  primes used to generate p*q = n, the public key.

  There's a more generalized form of the CRT which allows
  the divisors to not necessarily be coprime to start with
  (but with another stipulation about the remainders in
  that case).  See Knuth, Art of Computer Programming, Vol
  3, pg. 292.  Tweaking the code below to accommodate this
  case might be an exercise.  HINT:  you'd probably want an
  lcm function.

'''

from operator import mod
from operator import sub

def eea(a,b):
    """Extended Euclidean Algorithm for GCD"""
    v1 = [a,1,0]
    v2 = [b,0,1]
    print "  # eea(%2d, %2d):" % (a, b);
    while v2[0]<>0:
       p = v1[0] // v2[0] # floor division
       v2, v1 = map(sub, v1, [p*vi for vi in v2]), v2
       print "  #  %2d = (%2d * %2d) + (%2d * %2d)" % (
          v1[0], a, v1[1], b, v1[2])
    print "  #  %2d = gcd(%2d, %2d)" % (v1[0], a, b),
    print "  = (%2d * %2d) + (%2d * %2d)" % (a, v1[1], b, v1[2])
    return v1

def inverse(m,k):
     """
     Return b such that b*m mod k = 1, or 0 if no solution
     """
     v = eea(m,k)
     return (v[0]==1)*(v[1] % k)

def crt(ms,as):
     """
     Chinese Remainder Theorem:
     ms = list of coprimes.
     as = list of remainders when x is divided by ms
     M  = product of ms
     (ai is 'each in as', mi 'each in ms')

     The solution for x, modulo M will be:
     x = a1*M1*y1 + a2*M2*y2 + ... + ar*Mr*yr (mod M),
     where Mi = M/mi and yi = (Mi)^-1 (mod mi) for 1 <= i <= r.
     """

     M  = reduce(mul,ms)        # multiply ms together
     Ms = [M/mi for mi in ms]   # list of all M/mi
     ys = [inverse(Mi, mi) for Mi,mi in zip(Ms,ms)] # uses inverse,eea
     return reduce(add, [ai*Mi*yi for ai,Mi,yi in zip(as,Ms,ys)]) % M

if __name__ ==  '__main__':
  r = eea(5,7)
  print "eea(5,7) is ", r
  a, b = 5, 7
  g,x,y = eea(a,b)
  print "gcd(%d,%d) = %d = (%d*%d + %d*%d )." %(a,b,g, a,x,b,y)
