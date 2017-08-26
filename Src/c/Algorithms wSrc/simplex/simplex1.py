#!python2.5
# From http://taw9.hubpages.com/hub/Simplex-Algorithm-in-Python
# 2012-12-15 Sat 17:23 

# Fixed wrong pivot bug, 2013-01-02 Wed 09:31 
#   Bug: Cycles step 3 with wrong pivot on input below, see *.run file.

# How to import_file('F:/doc3/algo/simplex/simplex-py/simplex-tableau.py')
#   It gives error: SystemError: Parent module 'module' not loaded
#   2012-Dec-31 Mon 18:48
 
from __future__ import division
from numpy import *

class Tableau:
    def __init__(self, obj):
        self.obj = [1] + obj
        self.rows = []
        self.cons = []

    def add_constraint(self, expression, value):
        self.rows.append([0] + expression)
        self.cons.append(value)

    def _pivot_column(self):
        low = 0
        idx = 0
        for i in range(1, len(self.obj)-1):
            # print "col[%d]=%2.2f low=%2.2f" % (i,self.obj[i], low)
            if self.obj[i] < low:
                low = self.obj[i]
                idx = i
        if idx == 0: return -1
        return idx

    def _pivot_row(self, col):
        rhs = [self.rows[i][-1] for i in range(len(self.rows))]
        lhs = [self.rows[i][col] for i in range(len(self.rows))]
        ratio = []
        for i in range(len(rhs)):
            # print "lhs[%d]=%2.2f, rhs=%2.2f" % (i,lhs[i],rhs[i])
            # corrected bug: was lhs[i] == 0.
            if lhs[i] <= 0: 
                ratio.append(99999999 * abs(max(rhs)))
                continue
            ratio.append(rhs[i]/lhs[i])
        print "ratios:", [round(e) for e in ratio]
        # print "min ratio index:", argmin(ratio)
        return argmin(ratio)

    def display(self):
        print matrix([self.obj] + self.rows)

    def _pivot(self, row, col):
        e = self.rows[row][col]
        self.rows[row] /= e
        for r in range(len(self.rows)):
            if r == row: continue
            self.rows[r] = self.rows[r] - self.rows[r][col]*self.rows[row]
        self.obj = self.obj - self.obj[col]*self.rows[row]

    def _check(self):
        if min(self.obj[1:-1]) >= 0: return 1
        return 0
        
    def solve(self,max_steps):
        # build full tableau
        for i in range(len(self.rows)):
            self.obj += [0]
            ident = [0 for r in range(len(self.rows))]
            ident[i] = 1
            self.rows[i] += ident + [self.cons[i]]
            self.rows[i] = array(self.rows[i], dtype=float)
        self.obj = array(self.obj + [0], dtype=float)

        print "[ignore dummy first column]"
        print "solve:"
        self.display()
        step = 1
        while not self._check():
            c = self._pivot_column()
            r = self._pivot_row(c)
            self._pivot(r,c)
            print '\nstep=%d, pivot column: %s, row: %s' % (step, c+1,r+2)
            self.display()
            step = step + 1
            if step > max_steps:
              print "Too many steps, stopping"
              return
        print "[variable has value 0 if its column is not identity]"
        print "Solved in ", step, "steps"
            
if __name__ == '__main__':
    set_printoptions(precision=2)
    t = Tableau([-3,-1,-2])          # max z = 3x + 1y + 2z, st:
    t.add_constraint([1, 1, 3], 30)  # x + y + 3z <=  30
    t.add_constraint([2, 2, 5], 24)  # 2x + 2y + 5z <= 24
    t.add_constraint([4, 1, 2], 36)  # 4x + 1y + 2z <= 36
    t.solve(10) 
