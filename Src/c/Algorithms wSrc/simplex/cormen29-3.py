#!python2.5
# Solve cormen 29.3 using pysimplex
# 2012-12-15 Sat 17:23 
# 2012-Dec-31 Mon 18:48
# Bug? In output (cormen29-3-pivot.run), step 2, ratio: 1724999982 seems wrong.

from pysimplex import *

if __name__ == '__main__':
    set_printoptions(precision=2)
    t = Tableau([-3,-1,-2])          # max z = 3x + 1y + 2z, (change signs), st.
    t.add_constraint([1, 1, 3], 30)  # x + y + 3z <=  30
    t.add_constraint([2, 2, 5], 24)  # 2x + 2y + 5z <= 24
    t.add_constraint([4, 1, 2], 36)  # 4x + 1y + 2z <= 36
    t.solve(5) 
