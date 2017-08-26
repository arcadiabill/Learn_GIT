# For simplex tableau, paste this in maple V.4:
# 2012-Dec-31 Mon 17:51

read `pivot.mpl`;

A := matrix(3,5, [
    1, 5,  1,0,0,
    2, 3,  0,1,0,
    3, 1,  0,0,1 
  ]);

b := matrix(3,1, [8,6,6]);      # rhs
c := matrix(1,5, [-2,-1,0,0,0] ); # optimal function.
z := 0;

ratios(1);
pivot(3,1);
ratios(2);
pivot(2,2);
# Optimal is 4.28, at (x1,x2,x3)=(1.71,0.85,2)
