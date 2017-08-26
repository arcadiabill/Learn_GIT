# From Intermdiate Algebra, isbn=0618753524, by Larson and Hostetler
read `pivot.mpl`;
A := matrix(3, 5, [
  -1, 1, 1,0,0,
   1, 1, 0,1,0,
   2, 5, 0,0,1
  ]);

b := matrix(3,1, [11,27,90]);
c := matrix(1,6, [-4,-6, 0,0,0,0]);
z := 0;

ratios(2);
pivot(1,2);
ratios(1);
pivot(3,1);
ratios(3);
pivot(2,3);

# maximum is 132, with x1=15, x2=12.
