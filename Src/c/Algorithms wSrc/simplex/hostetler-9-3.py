#!python2.5
# Problem 19.5 from Rorres and Anton, Application linear algebra.
# 2013-Jan-02 Wed 10:06

from pysimplex import *

if __name__ == '__main__':
    set_printoptions(precision=2)
    t = Tableau([-4,-6,0])
    t.add_constraint([-1,1,1], 11)
    t.add_constraint([1, 1,0], 27)
    t.add_constraint([2, 5,0], 90)
    t.solve(5) 
    # maximum is 132, with x1=15, x2=12.
