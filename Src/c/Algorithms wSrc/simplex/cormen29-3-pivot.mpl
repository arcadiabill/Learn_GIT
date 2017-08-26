# For simplex tableau, paste this in maple V.4:
#   read `.../algo/opt/cormen29-3-pivot.in`;
# 2012-Dec-31 Mon 17:51

read `pivot.mpl`;

A := matrix(3,6, [
    1,1,3,  1,0,0,
    2,2,5,  0,1,0,
    4,1,2,  0,0,1
  ]);

b := matrix(3,1, [30,24,36]);
c := matrix(1,6, [-3,-1,-2,0,0,0]);
z := 0;

pivot(1,4);
ratios(1);
pivot(3,1);
ratios(3);
pivot(2,3);
ratios(2);
pivot(2,2);
