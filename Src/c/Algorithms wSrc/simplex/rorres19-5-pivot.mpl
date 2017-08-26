# For simplex tableau, paste this in maple V.4:
# 2012-Dec-31 Mon 17:51
# Manual directed simplex works.

read `pivot.mpl`;

A := matrix(3,6, [
    2,-1, 3,  1,0,0,
    1, 4,-2,  0,1,0,
    3, 0, 6,  0,0,1
  ]);

b := matrix(3,1, [5,1,4]);             # rhs
c := matrix(1,6, [-3, 1,-4,  0,0,0] ); # optimal function.
z := 0;

ratios(3);
pivot(3,3);
ratios(1);
pivot(2,1);
# Solution maximum is z=3.83=23/6, x1=1.16=7/6, x2=0, x3=0.08=1/2.
