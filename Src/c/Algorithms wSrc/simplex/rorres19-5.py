#!python2.5
# Problem 19.5 from Rorres and Anton, Application linear algebra.
# 2013-Jan-02 Wed 10:06

from pysimplex import *

if __name__ == '__main__':
    set_printoptions(precision=2)
    t = Tableau([-3,1,-4])         
    t.add_constraint([2,-1,+3], 5)
    t.add_constraint([1, 4,-2], 1)
    t.add_constraint([3, 0, 6], 4)
    t.solve(5) 
    print "Maple solution was max=3.833, x1=1.166, x2=0, x3=0.0833"
